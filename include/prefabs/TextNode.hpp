#pragma once

#include "system/all.hpp"
#include "system/Types/all.hpp"
#include "system/AssetTypes/all.hpp"

namespace Storm::Prefabs
{
    struct TextNodeConfig
    {
        FontAsset* font = AssetManager::get_asset<FontAsset>("font_default");
        size_t size = 12;

        // Where the origin of the text is set.
        Vec2<double> textOffset = {
            .x = 0,
            .y = 0
        };

        // The color of the test.
        SDL_Color color = {
            .r = 0xFF,
            .g = 0xFF,
            .b = 0xFF,
            .a = 0xFF
        };


        Rect<double> boundaries = {
            .position = {
                .x = 0,
                .y = 0
            },
            .size = {
                .x = 150,
                .y = 50
            }
        };
        
        std::string initialText = "";
    };

    class TextNode : public Node
    {
    protected:
        static void redraw_text_node(Node* slf);
        static void text_node_draw(Node* slf);

    public:
        // Constructor
        TextNode(TextNodeConfig config);
    };
};

