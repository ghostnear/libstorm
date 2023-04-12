#ifndef LIBSTORM_PREFABS_SPRITE_HPP
#define LIBSTORM_PREFABS_SPRITE_HPP

#include "system/all.hpp"

namespace Storm::Prefabs
{
    struct SpriteNodeConfig
    {
    };

    class SpriteNode : public Node
    {
    public:
        // Constructor
        SpriteNode(SpriteNodeConfig config);
    };
};

#endif