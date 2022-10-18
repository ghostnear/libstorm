#include "prefabs/textNode.hpp"

namespace Storm
{
    void redrawText(Node* slf)
    {
        auto font = slf -> getComponent<FontAsset>("text_font") -> get(*(slf -> getComponent<size_t>("text_size")));
        auto texturePtr = slf -> getComponent<SDL_Texture>("text_texture");
        auto textColor = *(slf -> getComponent<SDL_Color>("text_color"));
        // Invalid pointer, create texture
        if(texturePtr == nullptr)
        {
            texturePtr = SDL_CreateTextureFromSurface(
                Graphics::getSDL(),
                TTF_RenderText_Solid(
                    font,
                    slf -> getComponent<std::string>("text") -> c_str(),
                    textColor
                )
            );
            slf -> addComponent<SDL_Texture>(texturePtr, "text_texture");
        }
        else
        {
            SDL_DestroyTexture(texturePtr);
            redrawText(slf);
        }
    }

    void textNodeDraw(Node* slf)
    {
        // Rebuild texture if needed (needs the flag set on each change)
        auto redraw_flag = slf -> getComponent<bool>("needs_redrawing");
        if(*redraw_flag)
            redrawText(slf), *redraw_flag = false;

        // Draw the text to the screen
        auto boundaries = slf -> getComponent<Rect<double>>("boundaries");
        auto textureToDraw = slf -> getComponent<SDL_Texture>("text_texture");
        // TODO: dont make this on the heap, it's very costly
        SDL_Rect result_rect = {
            .x = int(boundaries -> position.x),
            .y = int(boundaries -> position.y),
            .w = int(boundaries -> size.x),
            .h = int(boundaries -> size.y)
        };
        SDL_RenderCopy(
            Graphics::getSDL(),
            textureToDraw,
            NULL,
            &result_rect
        );
    }

    TextNode::TextNode(TextNodeConfig config)
    {
        this -> addComponent<bool>(new bool(true), "needs_redrawing");
        this -> addComponent<Rect<double>>(new Rect<double>(config.boundaries), "boundaries");
        this -> addComponent<SDL_Texture>(nullptr, "text_texture");
        this -> addComponent<SDL_Color>(new SDL_Color(config.color), "text_color");
        this -> addComponent<size_t>(new size_t(config.size), "text_size");
        this -> addComponent<FontAsset>(config.font, "text_font");
        this -> addComponent<std::string>(new std::string(config.initialText), "text");
        this -> addFunction(textNodeDraw, "draw");
    }
}
