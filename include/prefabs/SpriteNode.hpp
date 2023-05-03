#pragma once

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
