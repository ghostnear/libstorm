#ifndef LIBSTORM_DEFAULT_SYSTEMS_HPP
#define LIBSTORM_DEFAULT_SYSTEMS_HPP

#include "deps.hpp"
#include "ecs.hpp"
#include "graphics.hpp"
#include "components.hpp"

namespace Storm
{
    class TextSystem : public System
    {
    public:
        void draw(World* w);
        void update(World* w, double dt);
    };
}

#endif