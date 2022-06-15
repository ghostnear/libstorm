#include "ecs/base.hpp"

namespace Storm
{
    EntityManager::EntityManager()
    {
        // Initialise the ECS
        _count = 0;
        for(Entity i = 0; i < LIBSTORM_MAX_ENTITIES; i++)
            _availableIDs.push(i);
    }

    Entity EntityManager::create()
    {
        // Fetch next id and create an entity with it
        Entity id = _availableIDs.front();
        _availableIDs.pop();
        _count++;

        return id;
    }

    uint32_t EntityManager::destroy(Entity id)
    {
        // Invalidate signature and destroy
        _entitySignatures[id].reset();
        _availableIDs.push(id);
        _count--;

        return EXIT_SUCCESS;
    }

    void EntityManager::setSignature(Entity entity, Signature sign)
    {
        _entitySignatures[entity] = sign;
    }

    Signature EntityManager::getSignature(Entity entity)
    {
        return _entitySignatures[entity];
    }

    uint32_t EntityManager::count()
    {
        return _count;
    }
};