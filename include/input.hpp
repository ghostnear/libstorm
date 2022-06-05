#ifndef LIBSTORM_INPUT_HPP
#define LIBSTORM_INPUT_HPP

#include "deps.hpp"
#include "window.hpp"

namespace Storm
{
    // Input singleton
    // https://stackoverflow.com/questions/1008019/c-singleton-design-pattern
    class Input
    {
        public:
            // Get the input instance
            static Input& getInstance()
            {
                // This is instantiated on first use and guaranteed to be the only one
                static Input instance;
                return instance;
            }

            // Do not allow for multiple instances
            Input(Input const&)          = delete;
            void operator=(Input const&)  = delete;

            // Methods
            static void pollEvents();

        private:
            // Constructor should be private
            Input();

            // Properties
            SDL_Event* event;
    };
}

#endif