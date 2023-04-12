#ifndef LIBSTORM_MATH_ALL
#define LIBSTORM_MATH_ALL

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
            return Vec2<TElem>({
                .x = aux_x,
                .y = aux_y
            });
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

#endif