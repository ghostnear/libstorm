#include "prefabs/TextNode.hpp"

namespace Storm::Prefabs
{
    void TextNode::redraw_text_node(Node* slf)
    {
        auto font = slf->get_component<FontAsset>("text_font")->get(*(slf->get_component<size_t>("text_size")));
        auto texturePtr = slf->get_component<SDL_Texture>("text_texture");
        auto textColor = *(slf->get_component<SDL_Color>("text_color"));
        
        // Invalid pointer, create texture
        if(texturePtr == nullptr)
        {
            SDL_Surface* renderedText =
                TTF_RenderText_Solid(
                    font,
                    slf->get_component<std::string>("text")->c_str(),
                    textColor
                );
            texturePtr = SDL_CreateTextureFromSurface(
                Graphics::get_SDL(),
                renderedText
            );
            SDL_FreeSurface(renderedText);
            slf->add_component<SDL_Texture>(
                "text_texture",
                texturePtr
            );
        }
        else
        {
            // Invalidate and force redraw
            SDL_DestroyTexture(texturePtr);
            slf->remove_component("text_texture");
            TextNode::redraw_text_node(slf);
        }
    }

    void TextNode::text_node_draw(Node* slf)
    {
        // Rebuild texture if needed (needs the flag set on each change)
        auto redraw_flag = slf->get_component<bool>("needs_redrawing");
        if(*redraw_flag)
            TextNode::redraw_text_node(slf), *redraw_flag = false;

        // Draw the text to the screen
        auto boundaries = slf->get_component<Rect<double>>("boundaries");
        auto textOffset = slf->get_component<Vec2<double>>("text_offset");
        auto textureToDraw = slf->get_component<SDL_Texture>("text_texture");
        // TODO: stop using the stack here
        static SDL_Rect result_rect; 
        result_rect = {
            .x = int(boundaries->position.x),
            .y = int(boundaries->position.y),
            .w = int(boundaries->size.x),
            .h = int(boundaries->size.y)
        };
        result_rect.x -= int(result_rect.w * textOffset->x);
        result_rect.y -= int(result_rect.h * textOffset->y);
        SDL_RenderCopy(
            Graphics::get_SDL(),
            textureToDraw,
            NULL,
            &result_rect
        );
    }

    TextNode::TextNode(TextNodeConfig config)
    {
        add_component<Vec2<double>>(
            "text_offset",
            new Vec2<double>(config.textOffset)
        );
        add_component<bool>(
            "needs_redrawing",
            new bool(true)
        );
        add_component<Rect<double>>(
            "boundaries",
            new Rect<double>(config.boundaries)
        );
        add_component<SDL_Texture>(
            "text_texture",
            nullptr
        );
        add_component<SDL_Color>(
            "text_color",
            new SDL_Color(config.color)
        );
        add_component<size_t>(
            "text_size",
            new size_t(config.size)
        );
        add_component<FontAsset>(
            "text_font",
            config.font
        );
        add_component<std::string>(
            "text",
            new std::string(config.initialText)
        );
        add_function(
            "draw",
            TextNode::text_node_draw
        );
    }
}
