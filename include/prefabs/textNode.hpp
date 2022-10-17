#ifndef LIBSTORM_PREFABS_TEXT_HPP
#define LIBSTORM_PREFABS_TEXT_HPP

#include "system/all.hpp"

namespace Storm
{
    struct TextNodeConfig
    {
        FontAsset* font = AssetManager::getAsset<FontAsset>("font_default");
        size_t size = 12;
        std::string initialText = "";
    };

    class TextNode : public Node
    {
    public:
        // Constructor
        TextNode(TextNodeConfig config);
    };
};

#endif
