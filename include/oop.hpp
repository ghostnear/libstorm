#ifndef LIBSTORM_OOP_HPP
#define LIBSTORM_OOP_HPP

#include "deps.hpp"
#include <queue>
#include <map>

namespace Storm
{
    #define LIBSTORM_MAX_OBJECTS 512

    // Alias for the id
    using Object = uint32_t;

    class OOPState;

    class BaseClass
    {
    public:
        virtual void onInit() = 0;
        virtual void onDestroy() = 0;
        virtual void draw(OOPState* gm) = 0;
        virtual void update(OOPState* gm, double dt) = 0;
    };

    class OOPWorld
    {
    public:
        OOPWorld()
        {
            _count = 0;
            for(Object i = 0; i < LIBSTORM_MAX_OBJECTS; i++)
                _availableIDs.push(i);
        }

        Object saveInstance(BaseClass* newInstance)
        {
            // Fetch next id and create an entity with it
            Object id = _availableIDs.front();
            _availableIDs.pop();
            _count++;
            _instances[id] = newInstance;

            return id;
        }

        void deleteInstance(Object id)
        {
            _count--;
            _availableIDs.push(id);
            _instances[id] = nullptr;
        }

        uint32_t count()
        {
            return _count;
        }

        void draw(OOPState* gm)
        {
            for(auto x : _instances)
                x.second -> draw(gm);
        }

        void update(OOPState* gm, double dt)
        {
            for(auto x : _instances)
                x.second -> update(gm, dt);
        }

    private:
        // Available id queue, when an entity gets destroyed the id is added here.
        std::queue<Object> _availableIDs;
        std::map<int, BaseClass*> _instances;

        // Alive objects
        uint32_t _count;
    };

};

#endif