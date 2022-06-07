#include "window.hpp"

namespace Storm
{
    Window::Window()
    {
        // Window flags
        uint32_t flags = SDL_WINDOW_OPENGL;

        // Create the SDL window
        window = SDL_CreateWindow(
            title.c_str(),
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            960, 540,
            flags);
        if(window == nullptr)
            isquit = true;
    }

    void Window::close()
    {
        Window::getInstance().isquit = true;
        SDL_DestroyWindow(getSDL());
    }

    void Window::setName(std::string newName)
    {
        SDL_SetWindowTitle(getSDL(), newName.c_str());
        Window::getInstance().title = newName;
    }

    void Window::setFullscreen(uint32_t flags)
    {
        // Save flags if valid
        if(flags == 0 || flags == SDL_WINDOW_FULLSCREEN || flags == SDL_WINDOW_FULLSCREEN_DESKTOP)
        {
            Window::getInstance().fullscreen_type = flags;
            Window::getInstance().fullscreen = (flags == 0);
            SDL_SetWindowFullscreen(getSDL(), flags);
        }
    }
}