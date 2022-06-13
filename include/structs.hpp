#ifndef LIBSTORM_STRUCTS_HPP
#define LIBSTORM_STRUCTS_HPP

namespace Storm
{
    template <typename T> 
    struct Vec2
    {
        T x, y;
    };

    template <typename T>
    struct Vec3
    {
        T x, y, z;
    };

    template <typename T>
    struct Transform2
    {
        Vec2<T> pos;
        double angle;
    };
}

#endif