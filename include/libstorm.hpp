#ifndef LIBSTORM_HPP
#define LIBSTORM_HPP

// Dependencies
#include <cstdio>
#include <string>
#include <SDL2/SDL.h>

// Lib internals
#include "msgbox.hpp"

namespace Storm
{
    int32_t Storm_Init();
    int32_t Storm_Quit();
}

#endif