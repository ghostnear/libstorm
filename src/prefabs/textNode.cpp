#include "prefabs/textNode.hpp"

namespace Storm
{
    void redrawText(Node* slf)
    {
        auto font = slf -> getComponent<FontAsset>("text_font") -> get(*(slf -> getComponent<size_t>("text_size")));
        auto texturePtr = slf -> getComponent<SDL_Texture>("text_texture");
        // Invalid pointer, create texture
        SDL_Color test;
        test.r = 0xFF;
        test.b = 0xFF;
        test.g = 0xFF;
        if(texturePtr == nullptr)
        {
            texturePtr = SDL_CreateTextureFromSurface(
                Graphics::getSDL(),
                TTF_RenderText_Solid(
                    font,
                    slf -> getComponent<std::string>("text") -> c_str(),
                    test
                )
            );
            slf -> addComponent<SDL_Texture>(texturePtr, "text_texture");
        }
        else {
            SDL_DestroyTexture(texturePtr);
            redrawText(slf);
        }
    }

    void textNodeDraw(Node* slf)
    {
        auto redraw_flag = slf -> getComponent<bool>("needs_redrawing");
        if(*redraw_flag)
            redrawText(slf), *redraw_flag = false;
        auto textureToDraw = slf -> getComponent<SDL_Texture>("text_texture");
        SDL_RenderCopy(
            Graphics::getSDL(),
            textureToDraw,
            NULL,
            NULL
        );
    }

    TextNode::TextNode(TextNodeConfig config)
    {
        this -> addComponent<bool>(new bool(true), "needs_redrawing");
        this -> addComponent<SDL_Texture>(nullptr, "text_texture");
        this -> addComponent<size_t>(new size_t(config.size), "text_size");
        this -> addComponent<FontAsset>(config.font, "text_font");
        this -> addComponent<std::string>(new std::string(config.initialText), "text");
        this -> addFunction(textNodeDraw, "draw");
    }
}
