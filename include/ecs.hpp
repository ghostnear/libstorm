#ifndef LIBSTORM_ENTITY_MANAGER_HPP
#define LIBSTORM_ENTITY_MANAGER_HPP

// Thanks to this, I understand ECS properly.
// https://austinmorlan.com/posts/entity_component_system/

#include "deps.hpp"
#include <queue>
#include <array>
#include <bitset>
#include <memory>
#include <set>
#include <unordered_map>

// 3000 entities should be enough
#define LIBSTORM_MAX_ENTITIES 3000

// 32 components should be enough
#define LIBSTORM_MAX_COMPONENTS 32

namespace Storm
{
    // Alias for the id
    using Entity = uint32_t;

    // Alias for component id
    using Component = uint8_t;

    // Component signature
    using Signature = std::bitset<LIBSTORM_MAX_COMPONENTS>;

    class EntityManager
    {
    public:
        // Constructor
        EntityManager();

        // Creates an entity and returns its id
        Entity create();

        // Destroys an entity and returns EXIT_SUCCESS if no errors occured.
        uint32_t destroy(Entity id);

        // Gets the current alive entity count
        uint32_t count();

        // Entity's signature get/set
        void setSignature(Entity entity, Signature sign);
        Signature getSignature(Entity entity);
    
    private:
        // Available id queue, when an entity gets destroyed the id is added here.
        std::queue<Entity> _availableIDs;

        // Array of signatures for components
        std::array<Signature, LIBSTORM_MAX_ENTITIES> _entitySignatures{};

        // Alive entities
        uint32_t _count;
    };

    // This exists so that the manager can tell the array an entity has been destroyed
    class ComponentArrayInterface
    {
    public:
        virtual ~ComponentArrayInterface() = default;
        virtual void onEntityDestroyed(Entity entity) = 0;
    };

    template<typename T>
    class ComponentArray : public ComponentArrayInterface
    {
    public:
        // Public methods
        void insert(Entity entity, T component)
        {
            // Put new entry at end and update the maps
            size_t _index = _count;
            _mapEntityToIndex[entity] = _index;
            _mapIndexToEntity[_index] = entity;
            _componentArray[_index] = component;
            ++_count;
        }

        void remove(Entity entity)
        {
            // Copy element at end into deleted element's place to maintain density
            size_t _removedIndex = _mapEntityToIndex[entity];
            size_t _lastIndex = _count - 1;
            _componentArray[_removedIndex] = _componentArray[_lastIndex];

            // Update map to point to moved spot
            Entity _lastEntity = _mapIndexToEntity[_lastIndex];
            _mapEntityToIndex[_lastEntity] = _removedIndex;
            _mapIndexToEntity[_removedIndex] = _lastEntity;

            _mapEntityToIndex.erase(entity);
            _mapIndexToEntity.erase(_lastIndex);

            --_count;
        }

        T& get(Entity entity)
        {
            return _componentArray[_mapEntityToIndex[entity]];
        }

        // Overwrite the interface methods
        void onEntityDestroyed(Entity entity) override
        {
            // If entity exists
            if(_mapEntityToIndex.find(entity) != _mapEntityToIndex.end())
                remove(entity);
        }

    private:
        std::array<T, LIBSTORM_MAX_ENTITIES> _componentArray;
        std::unordered_map<Entity, size_t> _mapEntityToIndex;
        std::unordered_map<size_t, Entity> _mapIndexToEntity;
        size_t _count;
    };

    class ComponentManager
    {
    public:
        template<typename T>
        void createComponent()
        {
            const char* typeName = typeid(T).name();
            _componentTypes.insert({typeName, mNextComponentType});
            _componentArrays.insert({typeName, std::make_shared<ComponentArray<T>>()});
            ++mNextComponentType;
        }

        template<typename T>
        Component getComponentType()
        {
            const char* typeName = typeid(T).name();
            return _componentTypes[typeName];
        }

        template<typename T>
        void addComponent(Entity entity, T component)
        {
            getComponentArray<T>() -> insert(entity, component);
        }

        template<typename T>
        void removeComponent(Entity entity)
        {
            getComponentArray<T>() -> remove(entity);
        }

        template<typename T>
        T& getComponent(Entity entity)
        {
            return getComponentArray<T>() -> get(entity);
        }

        void onEntityDestroyed(Entity entity)
        {
            for (auto const& pair : _componentArrays)
            {
                auto const& component = pair.second;
                component -> onEntityDestroyed(entity);
            }
        }

    private:
        std::unordered_map<const char*, Component> _componentTypes{};
        std::unordered_map<const char*, std::shared_ptr<ComponentArrayInterface>> _componentArrays{};
        Component mNextComponentType{};

        template<typename T>
        std::shared_ptr<ComponentArray<T>> getComponentArray()
        {
            const char* typeName = typeid(T).name();
            return std::static_pointer_cast<ComponentArray<T>>(_componentArrays[typeName]);
        }
    };

    // System base
    class System
    {
    public:
        std::set<Entity> _entities;
    };

    class SystemManager
    {
    public:
        template<typename T>
        std::shared_ptr<T> registerSystem()
        {
            const char* typeName = typeid(T).name();
            auto system = std::make_shared<T>();
            _systems.insert({typeName, system});
            return system;
        }

        template<typename T>
        void setSignature(Signature signature)
        {
            const char* typeName = typeid(T).name();
            _signatures.insert({typeName, signature});
        }

        void onEntityDestroyed(Entity entity)
        {
            for (auto const& pair : _systems)
            {
                auto const& system = pair.second;
                system -> _entities.erase(entity);
            }
        }

        void onEntitySignatureChanged(Entity entity, Signature entitySignature)
        {
            for (auto const& pair : _systems)
            {
                auto const& type = pair.first;
                auto const& system = pair.second;
                auto const& systemSignature = _signatures[type];

                if ((entitySignature & systemSignature) == systemSignature)
                    system -> _entities.insert(entity);
                else
                    system -> _entities.erase(entity);
            }
        }

    private:
        std::unordered_map<const char*, Signature> _signatures{};
        std::unordered_map<const char*, std::shared_ptr<System>> _systems{};
    };

    class World
    {
    public:
        World()
        {
            // Create pointers to each manager
            _componentManager   = std::make_unique<ComponentManager>();
            _entityManager      = std::make_unique<EntityManager>();
            _systemManager      = std::make_unique<SystemManager>();
        }


        // Entity methods
        Entity createEntity()
        {
            return _entityManager -> create();
        }

        void destroyEntity(Entity entity)
        {
            _entityManager -> destroy(entity);
            _componentManager -> onEntityDestroyed(entity);
            _systemManager -> onEntityDestroyed(entity);
        }


        // Component methods
        template<typename T>
        void registerComponent()
        {
            _componentManager -> createComponent<T>();
        }

        template<typename T>
        void addComponent(Entity entity, T component)
        {
            _componentManager -> createComponent<T>(entity, component);

            auto signature = _entityManager -> getSignature(entity);
            signature.set(_componentManager -> getComponentType<T>(), true);
            _entityManager -> setSignature(entity, signature);
            _systemManager -> onEntitySignatureChanged(entity, signature);
        }

        template<typename T>
        void removeComponent(Entity entity)
        {
            _componentManager -> removeComponent<T>(entity);

            auto signature = _entityManager -> getSignature(entity);
            signature.set(_componentManager -> getComponentType<T>(), false);
            _entityManager -> setSignature(entity, signature);
            _systemManager -> onEntitySignatureChanged(entity, signature);
        }

        template<typename T>
        T& getComponent(Entity entity)
        {
            return _componentManager -> getComponent<T>(entity);
        }

        template<typename T>
        Component getComponentType()
        {
            return _componentManager -> getComponentType<T>();
        }


        // System methods
        template<typename T>
        std::shared_ptr<T> registerSystem()
        {
            return _systemManager -> registerSystem<T>();
        }

        template<typename T>
        void setSystemSignature(Signature signature)
        {
            _systemManager -> setSignature<T>(signature);
        }

    private:
        std::unique_ptr<ComponentManager> _componentManager;
        std::unique_ptr<EntityManager> _entityManager;
        std::unique_ptr<SystemManager> _systemManager;
    };
};

#endif