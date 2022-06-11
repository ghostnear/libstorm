#ifndef LIBSTORM_DEFAULT_COMPONENTS_HPP
#define LIBSTORM_DEFAULT_COMPONENTS_HPP

#include "deps.hpp"

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

    struct Text
    {
        Transform2<double> tr;
        TTF_Font* font;
        std::string str;
    };

    static void assignDefaultComponents(World* w)
    {
        w -> registerComponent<Text>();
    }
}

#endif