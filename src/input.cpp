#include "input.hpp"

namespace Storm
{
    Input::Input()
    {
        event = new SDL_Event();
    }

    void Input::pollEvents()
    {
        SDL_Event* ev = Input::getInstance().event;
        while(SDL_PollEvent(ev))
        {
            switch(ev -> type)
            {
                case SDL_QUIT:
                case SDL_APP_TERMINATING:
                    Window::close();
                    break;
            }
        }
    }
}