#ifndef LIBSTORM_NODE_HPP
#define LIBSTORM_NODE_HPP

#include "deps.hpp"
#include <map>
#include <functional>

namespace Storm
{
    class Node;
    using NodeFunction = std::function<void(Node*)>;

    // Base structure of the engine.
    class Node
    {
    protected:
        std::map<std::string, void*> _components;
        std::map<std::string, Node*> _children;
        std::map<std::string, NodeFunction> _functions;
    public:
        // Add a component of specified type. Shouldn't have empty names.
        template<typename T> void addComponent(std::string name, T* pointer)
        {
            _components[name] = (void*)pointer;
        }

        /* ! Component types should be managed by the user, mismatching them can cause issues. ! */

        // Gets a component and returns as specified type.
        template<typename T> T* getComponent(std::string name)
        {
            return (T*)_components[name];
        }

        // Sets the component to a specified value and frees the value if required
        template<typename T> void setComponent(std::string name, T* value, bool free = false)
        {
            if(free)
                delete (T*)_components[name];
            addComponent(name, value);
        }


        // Removes a reference to a component. Data freeing is left to the user's discretion. (TODO not do that?)
        void removeComponent(std::string name)
        {
            _components[name] = nullptr;
        }

        // Add a child with a specified name. If empty, generate one (TODO).
        void addChild(Node* pointer, std::string name = "")
        {
            _children[name] = pointer;
        }

        // Gets a specific child.
        Node* getChild(std::string name)
        {
            return _children[name];
        }

        // Returns a reference to the children map.
        std::map<std::string, Node*>* getChildren()
        {
            return &_children;
        }

        // Remove a reference to a child. Data freeing is left to the user's discretion. (TODO not do that?)
        void removeChild(std::string name)
        {
            _children[name] = nullptr;
        }

        // Execute function on a node.
        void execute(std::string name)
        {
            if(_functions[name])
                _functions[name](this);
        }

        // Execute the function on self and on all children.
        void executeAll(std::string name)
        {
            execute(name);
            for(auto x : _children)
                x.second -> execute(name);
        }

        // Add function to function list.
        void addFunction(NodeFunction func, std::string name)
        {
            _functions[name] = func;
        }

        // Delete a function
        void deleteFunction(std::string name)
        {
            _functions[name] = NodeFunction(nullptr);
        }
    };
}

#endif
