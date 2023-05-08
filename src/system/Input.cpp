#include "system/Input.hpp"

namespace Storm
{
    Input& Input::getInstance()
    {
        // This is instantiated on first use and guaranteed to be the only one
        static Input instance;
        return instance;
    }

    void Input::onKey(SDL_Event* ev, bool pressed)
    {
        Input::getInstance()._currentState[ev->key.keysym.sym] = pressed;
    }

    bool Input::isKeyDown(SDL_Keycode key)
    {
        return Input::getInstance()._currentState[key];
    }

    bool Input::isKeyPressed(SDL_Keycode key)
    {
        return Input::getInstance()._currentState[key] && !Input::getInstance()._lastState[key];
    }

    bool Input::isKeyReleased(SDL_Keycode key)
    {
        return !Input::getInstance()._currentState[key] && Input::getInstance()._lastState[key];
    }

    void Input::pollEvents()
    {
    #ifndef VITA
        // Reset keyboard state
        Input::getInstance()._lastState = Input::getInstance()._currentState;
    #endif

        // Poll events
        SDL_Event* _ev = Input::getInstance()._event;
        while(SDL_PollEvent(_ev))
        {
            switch(_ev->type)
            {
                // App close
                case SDL_QUIT:
                case SDL_APP_TERMINATING:
                    Window::close();
                    break;

                // Window events
                case SDL_WINDOWEVENT:
                    Window::on_event(_ev);
                    break;

            #ifndef VITA
                // Key events
                case SDL_KEYUP:
                    Input::onKey(_ev, false);
                    break;
                case SDL_KEYDOWN:
                    Input::onKey(_ev, true);
                    break;
            #endif
            }
        }
    }
}