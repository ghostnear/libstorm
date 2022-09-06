#ifndef LIBSTORM_NODE_HPP
#define LIBSTORM_NODE_HPP

#include "deps.hpp"
#include <map>

namespace Storm
{
    // TODO: replace this with an engine config or something similar
    #define LIBSTORM_MAX_NODE_CHILDREN 512

    // Base structure.
    class Node
    {
    protected:
        std::map<std::string, void*> components;
        std::map<std::string, Node*> children;
        std::map<std::string, void*> functions;
    };
}

#endif
