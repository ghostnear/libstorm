#ifndef LIBSTORM_ENTITY_MANAGER_HPP
#define LIBSTORM_ENTITY_MANAGER_HPP

// Thanks to this, I understand ECS properly.
// https://austinmorlan.com/posts/entity_component_system/

#include "deps.hpp"
#include <queue>
#include <array>
#include <bitset>

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

    // Main manager
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
};

#endif