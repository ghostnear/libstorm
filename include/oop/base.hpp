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
        OOPWorld();

        // Methods
        uint32_t getCount();
        void draw(OOPState* gm);
        void update(OOPState* gm, double dt);
        Object saveInstance(BaseClass* newInstance);
        void deleteInstance(Object id);

    private:
        // Available id queue, when an entity gets destroyed the id is added here.
        std::queue<Object> _availableIDs;
        std::map<int, BaseClass*> _instances;

        // Alive objects
        uint32_t _count;
    };

};

#endif