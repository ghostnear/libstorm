#ifndef LIBSTORM_DEFAULT_SYSTEMS_HPP
#define LIBSTORM_DEFAULT_SYSTEMS_HPP

#include "deps.hpp"
#include "base.hpp"
#include "components.hpp"
#include "system/graphics.hpp"


namespace Storm
{
    class TextSystem : public System
    {
    public:
        void draw(ECSWorld* w);
        void update(ECSWorld* w, double dt);
    };
}

#endif