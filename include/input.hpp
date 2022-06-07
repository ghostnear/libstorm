#ifndef LIBSTORM_INPUT_HPP
#define LIBSTORM_INPUT_HPP

#include "deps.hpp"
#include "window.hpp"
#include <map>

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
            static bool isDown(SDL_Keycode key);
            static bool isPressed(SDL_Keycode key);
            static bool isReleased(SDL_Keycode key);

        private:
            // Constructor should be private
            Input();

            // Event handling
            SDL_Event* _event;

            // Internal event handlers
            static void onKey(SDL_Event* ev, bool pressed);

            // Keyboard handling
            std::map<SDL_Keycode, bool> _currentState;
            std::map<SDL_Keycode, bool> _lastState;
    };
}

#endif