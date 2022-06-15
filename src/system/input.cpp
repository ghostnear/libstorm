#include "system/input.hpp"

// TODO: add key bindings to input so events can occur

namespace Storm
{
    // Macros for better readability
    #define lastKeyboardState Input::getInstance()._lastState
    #define currentKeyboardState Input::getInstance()._currentState

    Input& Input::getInstance()
    {
        // This is instantiated on first use and guaranteed to be the only one
        static Input instance;
        return instance;
    }

    void Input::onKey(SDL_Event* ev, bool pressed)
    {
        currentKeyboardState[ev -> key.keysym.sym] = pressed;
    }

    bool Input::isKeyDown(SDL_Keycode key)
    {
        return currentKeyboardState[key];
    }

    bool Input::isKeyPressed(SDL_Keycode key)
    {
        return currentKeyboardState[key] && !lastKeyboardState[key];
    }

    bool Input::isKeyReleased(SDL_Keycode key)
    {
        return !currentKeyboardState[key] && lastKeyboardState[key];
    }

    void Input::pollEvents()
    {
        // Reset keyboard state
        lastKeyboardState = currentKeyboardState;

        // Poll events
        SDL_Event* _ev = Input::getInstance()._event;
        while(SDL_PollEvent(_ev))
        {
            switch(_ev -> type)
            {
                // App close
                case SDL_QUIT:
                case SDL_APP_TERMINATING:
                    Window::close();
                    break;

                // Window events
                case SDL_WINDOWEVENT:
                    Window::onEvent(_ev);
                    break;

                // Key events
                case SDL_KEYUP:
                    Input::onKey(_ev, false);
                    break;
                case SDL_KEYDOWN:
                    Input::onKey(_ev, true);
                    break;
            }
        }
    }

    #undef currentKeyboardState
    #undef lastKeyboardState
}