#include "prefabs/TextNode.hpp"
#include "system/Types/Texture.hpp"
#include <SDL2/SDL_ttf.h>

namespace Storm::Prefabs
{
    void TextNode::redraw_text_node(Node* slf)
    {
        auto font = slf->get_component<FontAsset>("text_font")->get(*(slf->get_component<size_t>("text_size")));
        if(font == nullptr)
            return;

        auto texturePtr = slf->get_component<Texture>("text_texture");
        
        if(texturePtr == nullptr)
        {
            SDL_Surface* renderedText =
                TTF_RenderText_Solid(
                    font,
                    slf->get_component<std::string>("text")->c_str(),
                    *(slf->get_component<SDL_Color>("text_color"))
                );

            if(renderedText != nullptr)
            {
                slf->set_component<Texture>(
                    "text_texture",
                    new Texture(
                        SDL_CreateTextureFromSurface(
                            Graphics::get_SDL(),
                            renderedText
                        )
                    )
                );
            }

            SDL_FreeSurface(renderedText);
            return;
        }

        // Invalidate and force redraw otherwise.
        slf->remove_component<Texture>("text_texture");
        TextNode::redraw_text_node(slf);
    }

    void TextNode::text_node_draw(Node* slf)
    {
        // Make sure it is actually drawable.
        auto drawable = slf->get_component<bool>("drawable");
        if(!*drawable)
            return;

        // Make sure you have a font first.
        auto fontAsset = slf->get_component<FontAsset>("text_font");
        if(fontAsset == nullptr)
            return;

        // Rebuild texture if needed (needs the flag set on each change)
        auto redraw_flag = slf->get_component<bool>("needs_redrawing");
        if(*redraw_flag)
            TextNode::redraw_text_node(slf), *redraw_flag = false;

        // Draw the text to the screen
        auto textureToDraw = slf->get_component<Texture>("text_texture");
        if(textureToDraw == nullptr)
            return;
        
        auto boundaries = slf->get_component<Rect<double>>("boundaries");
        auto textOffset = slf->get_component<Vec2<double>>("text_offset");

        static SDL_Rect result_rect; 
        result_rect = {
            .x = int(boundaries->position.x),
            .y = int(boundaries->position.y),
            .w = int(boundaries->size.x),
            .h = int(boundaries->size.y)
        };

        result_rect.x -= int(result_rect.w * textOffset->x);
        result_rect.y -= int(result_rect.h * textOffset->y);

        if(textureToDraw->get() != nullptr)
        {
            SDL_RenderCopy(
                Graphics::get_SDL(),
                textureToDraw->get(),
                NULL,
                &result_rect
            );
        }
    }

    TextNode::TextNode(TextNodeConfig config)
    {
        set_component<Vec2<double>>(
            "text_offset",
            new Vec2<double>(config.textOffset)
        );
        set_component<bool>(
            "needs_redrawing",
            new bool(true)
        );
        set_component<bool>(
            "drawable",
            new bool(true)
        );
        set_component<Rect<double>>(
            "boundaries",
            new Rect<double>(config.boundaries)
        );
        set_component<Texture>(
            "text_texture",
            nullptr
        );
        set_component<SDL_Color>(
            "text_color",
            new SDL_Color(config.color)
        );
        set_component<size_t>(
            "text_size",
            new size_t(config.size)
        );
        set_component<FontAsset>(
            "text_font",
            config.font
        );
        set_component<std::string>(
            "text",
            new std::string(config.initialText)
        );
        add_function(
            "draw",
            TextNode::text_node_draw
        );
    }

    TextNode::~TextNode()
    {
        remove_component<bool>("drawable");
        remove_component<Vec2<double>>("text_offset");
        remove_component<bool>("needs_redrawing");
        remove_component<Rect<double>>("boundaries");
        remove_component<Texture>("text_texture");
        remove_component<SDL_Color>("text_color");
        remove_component<size_t>("text_size");
        remove_component<FontAsset>("text_font");
        remove_component<std::string>("text");
        remove_function("draw");
    }
}
