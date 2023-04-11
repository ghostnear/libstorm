#ifndef LIBSTORM_MATH_ALL
#define LIBSTORM_MATH_ALL

namespace Storm
{
    template <typename T> 
    struct Vec2
    {
        T x, y;
        
        template <typename Y>
        Vec2<T> multiplyByComponents(Vec2<Y> arg)
        {
            // TODO: simplify
            T aux_x = x * arg.x;
            T aux_y = y * arg.y;
            return Vec2<T>({
                .x = aux_x,
                .y = aux_y
            });
        }
    };

    template <typename T>
    struct Vec3
    {
        T x, y, z;
    };

    template <typename T>
    struct Rect
    {
        Vec2<T> position, size;
    };

    template <typename T>
    struct Transform2
    {
        Vec2<T> position;
        double angle;
    };
}

#endif