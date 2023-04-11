#include "prefabs/TextNode.hpp"

namespace Storm::Prefabs
{
    void TextNode::redrawTextNode(Node* slf)
    {
        auto font = slf->getComponent<FontAsset>("text_font")->get(*(slf->getComponent<size_t>("text_size")));
        auto texturePtr = slf->getComponent<SDL_Texture>("text_texture");
        auto textColor = *(slf->getComponent<SDL_Color>("text_color"));
        // Invalid pointer, create texture
        if(texturePtr == nullptr)
        {
            SDL_Surface* renderedText =
                TTF_RenderText_Solid(
                    font,
                    slf->getComponent<std::string>("text")->c_str(),
                    textColor
                );
            texturePtr = SDL_CreateTextureFromSurface(
                Graphics::getSDL(),
                renderedText
            );
            SDL_FreeSurface(renderedText);
            slf->addComponent<SDL_Texture>(
                "text_texture",
                texturePtr
            );
        }
        else
        {
            // Invalidate and force redraw
            SDL_DestroyTexture(texturePtr);
            slf->removeComponent("text_texture");
            TextNode::redrawTextNode(slf);
        }
    }

    void TextNode::textNodeDraw(Node* slf)
    {
        // Rebuild texture if needed (needs the flag set on each change)
        auto redraw_flag = slf->getComponent<bool>("needs_redrawing");
        if(*redraw_flag)
            TextNode::redrawTextNode(slf), *redraw_flag = false;

        // Draw the text to the screen
        auto boundaries = slf->getComponent<Rect<double>>("boundaries");
        auto textOffset = slf->getComponent<Vec2<double>>("text_offset");
        auto textureToDraw = slf->getComponent<SDL_Texture>("text_texture");
        // TODO: stop using the stack here
        SDL_Rect result_rect = {
            .x = int(boundaries->position.x),
            .y = int(boundaries->position.y),
            .w = int(boundaries->size.x),
            .h = int(boundaries->size.y)
        };
        result_rect.x -= int(result_rect.w * textOffset->x);
        result_rect.y -= int(result_rect.h * textOffset->y);
        SDL_RenderCopy(
            Graphics::getSDL(),
            textureToDraw,
            NULL,
            &result_rect
        );
    }

    TextNode::TextNode(TextNodeConfig config)
    {
        addComponent<Vec2<double>>(
            "text_offset",
            new Vec2<double>(config.textOffset)
        );
        addComponent<bool>(
            "needs_redrawing",
            new bool(true)
        );
        addComponent<Rect<double>>(
            "boundaries",
            new Rect<double>(config.boundaries)
        );
        addComponent<SDL_Texture>(
            "text_texture",
            nullptr
        );
        addComponent<SDL_Color>(
            "text_color",
            new SDL_Color(config.color)
        );
        addComponent<size_t>(
            "text_size",
            new size_t(config.size)
        );
        addComponent<FontAsset>(
            "text_font",
            config.font
        );
        addComponent<std::string>(
            "text",
            new std::string(config.initialText)
        );
        addFunction(TextNode::textNodeDraw, "draw");
    }
}
