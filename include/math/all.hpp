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

        template<typename T>
        Vec2<TElem> operator+(Vec2<T> arg)
        {
            return {
                .x = x + arg.x,
                .y = y + arg.y
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
    };

    template<typename TElem>
    struct Transform2
    {
        Vec2<TElem> position;
        double angle;
    };
}
