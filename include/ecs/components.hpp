#ifndef LIBSTORM_DEFAULT_COMPONENTS_HPP
#define LIBSTORM_DEFAULT_COMPONENTS_HPP

#include "deps.hpp"

namespace Storm
{
    struct Text
    {
        Transform2<double> tr;
        TTF_Font* font;
        std::string str;
    };

    static void assignDefaultComponents(ECSWorld* w)
    {
        w -> registerComponent<Text>();
    }
}

#endif