#include "input.hpp"

namespace Storm
{
    // Macros for better readability
    #define lastKeyboardState Input::getInstance()._lastState
    #define currentKeyboardState Input::getInstance()._currentState

    Input::Input()
    {
        _event = new SDL_Event();
    }

    void Input::onKey(SDL_Event* ev, bool pressed)
    {
        currentKeyboardState[ev -> key.keysym.sym] = pressed;
    }

    bool Input::isDown(SDL_Keycode key)
    {
        return currentKeyboardState[key];
    }

    bool Input::isPressed(SDL_Keycode key)
    {
        return currentKeyboardState[key] && !lastKeyboardState[key];
    }

    bool Input::isReleased(SDL_Keycode key)
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
                case SDL_QUIT:
                case SDL_APP_TERMINATING:
                    Window::close();
                    break;

                case SDL_KEYUP:
                    Input::onKey(_ev, false);
                    break;

                case SDL_KEYDOWN:
                    Input::onKey(_ev, true);
                    break;
            }
        }
    }
}