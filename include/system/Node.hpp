#pragma once

#include "deps.hpp"
#include <map>
#include <functional>
#include <memory>

namespace Storm
{
    class Node;
    using NodeFunction = std::function<void(Node*)>;

    // Base structure of the engine.
    class Node
    {
    protected:
        std::map<std::string, void*> _components;
        std::map<std::string, std::shared_ptr<Node>> _children;
        std::map<std::string, NodeFunction> _functions;

    public:
        // Add a component of specified type. Shouldn't have empty names.
        template<typename TElem> void set_component(std::string name, TElem* value)
        {
            std::shared_ptr<TElem>* newComponent = new std::shared_ptr<TElem>(value);
            _components[name] = newComponent;
        }

        // Destructor
        ~Node()
        {
            execute("free_node");
        }

        /* ! Component types should be managed by the user, mismatching them can cause issues. ! */

        // Gets a component and returns as specified type.
        template<typename TElem> std::shared_ptr<TElem> get_component(std::string name)
        {
            return *((std::shared_ptr<TElem>*)_components[name]);
        }

        // Removes a reference to a component.
        template<typename TElem> void remove_component(std::string name)
        {
            auto component = _components.find(name);
            if(component != _components.end())
            {
                ((std::shared_ptr<TElem>*)component->second)->reset();
                delete ((std::shared_ptr<TElem>*)component->second);
                _components.erase(component);
            }
        }

        // Add a child with a specified name. If empty, generate one (TODO).
        void add_child(Node* node, std::string name = "")
        {
            _children[name] = std::shared_ptr<Node>(node);
        }

        // Gets a specific child.
        std::shared_ptr<Node> get_child(std::string name)
        {
            return _children[name];
        }

        // Remove a reference to a child. Data freeing is left to the user's discretion. (TODO not do that?)
        void remove_child(std::string name)
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
        void execute_all(std::string name)
        {
            execute(name);
            for(auto child : _children)
                child.second->execute(name);
        }

        // Add function to function list.
        void add_function(std::string name, NodeFunction func)
        {
            _functions[name] = func;
        }

        // Delete a function
        void delete_function(std::string name)
        {
            auto iterator = _functions.find(name);
            if(iterator != _functions.end())
                _functions.erase(iterator);

            // Functions don't need freeing as they are statically defined in the code data.
        }
    };
}
