#pragma once

#include "system/all.hpp"
#include "system/Types/all.hpp"
#include "system/AssetTypes/all.hpp"

namespace Storm::Prefabs
{
    struct SpriteNodeConfig
    {
        ImageAsset* image = AssetManager::get_asset<ImageAsset>("sprite_default");
        Vec2<double> position = { 0, 0 };
        Vec2<double> scale = { 1, 1 };
        Vec2<double> offset = { 0, 0 };
        double alpha = 1;
    };

    class SpriteNode : public Node
    {
    protected:
        static void sprite_node_draw(Node* slf);

    public:
        // Constructor
        SpriteNode(SpriteNodeConfig config);

        // Destructor
        ~SpriteNode();
    };
};
