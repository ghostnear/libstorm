#ifndef LIBSTORM_HPP
#define LIBSTORM_HPP

#include "ecs.hpp"
#include "input.hpp"
#include "window.hpp"
#include "msgbox.hpp"
#include "graphics.hpp"
#include "gamemanager.hpp"

namespace Storm
{
    int32_t StormInit();
    int32_t StormQuit(int32_t ret_val);
}

#endif