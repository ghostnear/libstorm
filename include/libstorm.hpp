#ifndef LIBSTORM_HPP
#define LIBSTORM_HPP

#include "deps.hpp"
#include "ecs/all.hpp"
#include "oop/all.hpp"
#include "system/all.hpp"

namespace Storm
{
    int32_t StormInit();
    int32_t StormQuit(int32_t ret_val);

    namespace Utils
    {
        template<typename T>
        inline std::string to_string(T arg)
        {
            std::ostringstream ss;
            ss << arg;
            return ss.str();
        }

        // Intersects 2 rects and returns the resulting intersection.
        // If the result is nullptr then that means the rects don't intersect
        SDL_Rect* intersectRects(SDL_Rect* a, SDL_Rect* b);
    };
}

#endif