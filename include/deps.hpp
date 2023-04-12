#ifndef LIBSTORM_DEPS_HPP
#define LIBSTORM_DEPS_HPP

// Dependencies required everywhere
#include <cstdio>
#include <sstream>
#include <iostream>
#include <string>
#include "math/all.hpp"

// Platform dependent dependencies
#ifndef WIN
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_image.h>
    #include <SDL2/SDL_ttf.h>
#else
    #include <SDL.h>
    #include <SDL_image.h>
    #include <SDL_ttf.h>
#endif

#ifdef VITA
    #include <psp2/kernel/processmgr.h>
#endif

namespace Utils
{
    template<typename T>
    inline std::string to_string(T arg)
    {
        std::ostringstream _ss;
        _ss << arg;
        return _ss.str();
    }

    // Intersects 2 rects and returns the resulting intersection.
    // If the result is nullptr then that means the rects don't intersect
    SDL_Rect* intersect_rects(SDL_Rect* a, SDL_Rect* b);

    // Removes the file name from the path
    // ex: ./assets/lists.json becomes ./assets/
    std::string remove_file_name_from_path(std::string path);
};

#endif
