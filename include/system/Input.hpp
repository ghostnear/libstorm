#ifndef LIBSTORM_INPUT_HPP
#define LIBSTORM_INPUT_HPP

#include "deps.hpp"
#include "Window.hpp"
#include <map>

namespace Storm
{
    // Input singleton
    // https://stackoverflow.com/questions/1008019/c-singleton-design-pattern
    class Input
    {
        public:
            // Do not allow for multiple instances
            Input(Input const&)          = delete;
            void operator=(Input const&)  = delete;

            // Methods
            static Input& getInstance();
            static void pollEvents();
            static bool isKeyDown(SDL_Keycode key);
            static bool isKeyPressed(SDL_Keycode key);
            static bool isKeyReleased(SDL_Keycode key);
            static void onKey(SDL_Event* ev, bool pressed);

        private:
            // Constructor should be private
            Input() {}

            // Event handling
            SDL_Event* _event = new SDL_Event();

            // Keyboard handling
            std::map<SDL_Keycode, bool> _currentState;
            std::map<SDL_Keycode, bool> _lastState;
    };
}

#endif