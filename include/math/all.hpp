#pragma once

#include <SDL2/SDL.h>

namespace Storm
{
    template<typename TElem> 
    struct Vec2
    {
        TElem x, y;
        
        template<typename T>
        Vec2<TElem> multiply_by_components(Vec2<T> arg)
        {
            // TODO: simplify
            TElem aux_x = x * arg.x;
            TElem aux_y = y * arg.y;
            return {
                .x = aux_x,
                .y = aux_y
            };
        }
    };

    template<typename TElem>
    struct Vec3
    {
        TElem x, y, z;
    };

    template<typename TElem>
    struct Rect
    {
        Vec2<TElem> position, size;

        SDL_Rect to_SDL()
        {
            SDL_Rect result;
            result.x = position.x;
            result.y = position.y;
            result.w = size.x;
            result.h = size.y;
            return result;
        }
    };

    template<typename TElem>
    struct Transform2
    {
        Vec2<TElem> position;
        double angle;
    };
}
