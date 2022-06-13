#ifndef LIBSTORM_HPP
#define LIBSTORM_HPP

#include "oop.hpp"
#include "ecs.hpp"
#include "input.hpp"
#include "window.hpp"
#include "msgbox.hpp"
#include "systems.hpp"
#include "graphics.hpp"
#include "components.hpp"
#include "gamemanager.hpp"

namespace Storm
{
    int32_t StormInit();
    int32_t StormQuit(int32_t ret_val);

    namespace Utils
    {
        template<typename T>
        std::string to_string(T arg)
        {
            std::ostringstream ss;
            ss << arg;
            return ss.str();
        }
    };
}

#endif