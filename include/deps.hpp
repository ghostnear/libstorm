#ifndef LIBSTORM_DEPS_HPP
#define LIBSTORM_DEPS_HPP

#include <cstdio>
#include <sstream>
#include <iostream>
#include "structs.hpp"

#ifndef BUILD_TYPE_WIN
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_image.h>
    #include <SDL2/SDL_ttf.h>
#else
    #include <SDL.h>
    #include <SDL_image.h>
    #include <SDL_ttf.h>
#endif

#ifdef BUILD_TYPE_VITA
    #include <psp2/kernel/processmgr.h>
#endif

#endif