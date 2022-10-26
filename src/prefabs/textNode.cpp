#include "prefabs/textNode.hpp"

namespace Storm
{
    void TextNode::redrawTextNode(Node* slf)
    {
        auto font = slf -> getComponent<FontAsset>("text_font") -> get(*(slf -> getComponent<size_t>("text_size")));
        auto texturePtr = slf -> getComponent<SDL_Texture>("text_texture");
        auto textColor = *(slf -> getComponent<SDL_Color>("text_color"));
        // Invalid pointer, create texture
        if(texturePtr == nullptr)
        {
            SDL_Surface* renderedText =
                TTF_RenderText_Solid(
                    font,
                    slf -> getComponent<std::string>("text") -> c_str(),
                    textColor
                );
            texturePtr = SDL_CreateTextureFromSurface(
                Graphics::getSDL(),
                renderedText
            );
            SDL_FreeSurface(renderedText);
            slf -> addComponent<SDL_Texture>(texturePtr, "text_texture");
        }
        else
        {
            // Invalidate and force redraw
            SDL_DestroyTexture(texturePtr);
            slf -> addComponent<SDL_Texture>(nullptr, "text_texture");
            TextNode::redrawTextNode(slf);
        }
    }

    void TextNode::textNodeDraw(Node* slf)
    {
        // Rebuild texture if needed (needs the flag set on each change)
        auto redraw_flag = slf -> getComponent<bool>("needs_redrawing");
        if(*redraw_flag)
            TextNode::redrawTextNode(slf), *redraw_flag = false;

        // Draw the text to the screen
        auto boundaries = slf -> getComponent<Rect<double>>("boundaries");
        auto textOffset = slf -> getComponent<Vec2<double>>("text_offset");
        auto textureToDraw = slf -> getComponent<SDL_Texture>("text_texture");
        // TODO: dont make this on the heap, it's very costly
        SDL_Rect result_rect = {
            .x = int(boundaries -> position.x),
            .y = int(boundaries -> position.y),
            .w = int(boundaries -> size.x),
            .h = int(boundaries -> size.y)
        };
        result_rect.x -= int(result_rect.w * textOffset -> x);
        result_rect.y -= int(result_rect.h * textOffset -> y);
        SDL_RenderCopy(
            Graphics::getSDL(),
            textureToDraw,
            NULL,
            &result_rect
        );
    }

    TextNode::TextNode(TextNodeConfig config)
    {
        this -> addComponent<Vec2<double>>(new Vec2<double>(config.textOffset), "text_offset");
        this -> addComponent<bool>(new bool(true), "needs_redrawing");
        this -> addComponent<Rect<double>>(new Rect<double>(config.boundaries), "boundaries");
        this -> addComponent<SDL_Texture>(nullptr, "text_texture");
        this -> addComponent<SDL_Color>(new SDL_Color(config.color), "text_color");
        this -> addComponent<size_t>(new size_t(config.size), "text_size");
        this -> addComponent<FontAsset>(config.font, "text_font");
        this -> addComponent<std::string>(new std::string(config.initialText), "text");
        this -> addFunction(TextNode::textNodeDraw, "draw");
    }
}
