#include "prefabs/SpriteNode.hpp"
#include "prefabs/TextNode.hpp"

namespace Storm::Prefabs
{
    void SpriteNode::sprite_node_draw(Node* slf)
    {
        auto sprite = slf->get_component<ImageAsset>("sprite_image");
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
        SDL_SetRenderDrawBlendMode(Graphics::get_SDL(), SDL_BLENDMODE_BLEND);

        if(sprite != nullptr)
            SDL_RenderCopy(Graphics::get_SDL(), sprite->get(), NULL, &displayRect);

        SDL_SetRenderDrawBlendMode(Graphics::get_SDL(), SDL_BLENDMODE_NONE);
        SDL_SetTextureAlphaMod(sprite->get(), 255);
    }

    SpriteNode::SpriteNode(SpriteNodeConfig config)
    {
        set_component<double>(
            "sprite_alpha",
            new double(config.alpha)
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
}
