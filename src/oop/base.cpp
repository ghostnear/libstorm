#include "oop/base.hpp"

namespace Storm
{
    OOPWorld::OOPWorld()
    {
        _count = 0;
        for(Object i = 0; i < LIBSTORM_MAX_OBJECTS; i++)
            _availableIDs.push(i);
    }

    uint32_t OOPWorld::getCount()
    {
        return _count;
    }

    void OOPWorld::draw(OOPState* gm)
    {
        for(auto x : _instances)
            x.second -> draw(gm);
    }

    void OOPWorld::update(OOPState* gm, double dt)
    {
        for(auto x : _instances)
            x.second -> update(gm, dt);
    }

    Object OOPWorld::saveInstance(BaseClass* newInstance)
    {
        // Fetch next id and create an entity with it
        Object id = _availableIDs.front();
        _availableIDs.pop();
        _count++;
        _instances[id] = newInstance;
        newInstance -> onInit();

        return id;
    }

    void OOPWorld::deleteInstance(Object id)
    {
        _count--;
        _availableIDs.push(id);
        _instances[id] -> onDestroy();
        _instances[id] = nullptr;
    }
};