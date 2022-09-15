#include "prefabs/textNode.hpp"

namespace Storm
{
    void textNodeDraw(Node* slf)
    {
        auto text = slf -> getComponent<std::string>("text");
        //printf(text -> c_str());
    }

    TextNode::TextNode(TextNodeConfig config, std::string initial_message)
    {
        this -> addComponent<bool>(new bool(true), "needs_redrawing");
        this -> addComponent<std::string>(new std::string(initial_message), "text");
        this -> addFunction(textNodeDraw, "draw");
    }
}
