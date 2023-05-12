#include "prefabs/SpriteNode.hpp"
#include "prefabs/TextNode.hpp"

namespace Storm::Prefabs
{
    void SpriteNode::sprite_node_draw(Node* slf)
    {
        // Make sure the sprite is drawable.
        auto drawable = slf->get_component<bool>("drawable");
        if(!*drawable)
            return;

        // Make sure the image exists.
        auto sprite = slf->get_component<ImageAsset>("sprite_image");
        if(sprite == nullptr)
            return;

        auto position = slf->get_component<Vec2<double>>("sprite_position");

        static SDL_Rect displayRect;
        displayRect = {
            .x = (int)position->x,
            .y = (int)position->y
        };

        // Get sprite size.
        SDL_QueryTexture(
            sprite->get(), NULL, NULL,
            &displayRect.w, &displayRect.h
        );

        auto scale = slf->get_component<Vec2<double>>("sprite_scale");
        displayRect.w *= scale->x;
        displayRect.h *= scale->y;

        auto offset = slf->get_component<Vec2<double>>("sprite_offset");
        displayRect.x -= (int)(displayRect.w * offset->x);
        displayRect.y -= (int)(displayRect.h * offset->y);

        auto alpha = slf->get_component<double>("sprite_alpha");
        SDL_SetTextureAlphaMod(sprite->get(), (Uint8)(*alpha * 255));

        SDL_RenderCopy(Graphics::get_SDL(), sprite->get(), NULL, &displayRect);
    }

    SpriteNode::SpriteNode(SpriteNodeConfig config)
    {
        set_component<double>(
            "sprite_alpha",
            new double(config.alpha)
        );
        set_component<bool>(
            "drawable",
            new bool(true)
        );
        set_component<Vec2<double>>(
            "sprite_position",
            new Vec2<double>(config.position)
        );
        set_component<Vec2<double>>(
            "sprite_scale",
            new Vec2<double>(config.scale)
        );
        set_component<Vec2<double>>(
            "sprite_offset",
            new Vec2<double>(config.offset)
        );
        set_component<ImageAsset>(
            "sprite_image",
            config.image
        );
        add_function(
            "draw",
            SpriteNode::sprite_node_draw
        );
    }

    SpriteNode::~SpriteNode()
    {
        remove_component<bool>("drawable");
        remove_component<double>("sprite_alpha");
        remove_component<Vec2<double>>("sprite_position");
        remove_component<Vec2<double>>("sprite_scale");
        remove_component<Vec2<double>>("sprite_offset");
        remove_component<ImageAsset>("sprite_image");
        remove_function("draw");
    }
}
