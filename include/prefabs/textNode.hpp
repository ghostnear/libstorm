#ifndef LIBSTORM_PREFABS_TEXT_HPP
#define LIBSTORM_PREFABS_TEXT_HPP

#include "system/all.hpp"

namespace Storm
{
    struct TextNodeConfig
    {
        FontAsset* font = AssetManager::getAsset<FontAsset>("font_default");
        size_t size = 12;
        Vec2<double> textOffset = {
            .x = 0,
            .y = 0
        };
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
    public:
        // Constructor
        TextNode(TextNodeConfig config);

        static void redrawTextNode(Node* slf);
        static void textNodeDraw(Node* slf);
    };
};

#endif
