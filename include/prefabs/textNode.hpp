#ifndef LIBSTORM_PREFABS_TEXT_HPP
#define LIBSTORM_PREFABS_TEXT_HPP

#include "system/all.hpp"

namespace Storm
{
    struct TextNodeConfig
    {
        
    };

    class TextNode : public Node
    {
    public:
        // Constructor
        TextNode(TextNodeConfig config, std::string initial_message = "");
    };
};

#endif
