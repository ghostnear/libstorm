#include "window.hpp"

namespace Storm
{
    #define win Window::getInstance()

    Window::Window()
    {
        // Window flags
        uint32_t flags = SDL_WINDOW_RESIZABLE | fullscreen_type;

        // Create the SDL window
        window = SDL_CreateWindow(
            title.c_str(),
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            size_x, size_y,
            flags);
        if(window == nullptr)
            isquit = true;
    }

    void Window::close()
    {
        win.isquit = true;
        SDL_DestroyWindow(getSDL());
    }

    void Window::setName(std::string newName)
    {
        SDL_SetWindowTitle(getSDL(), newName.c_str());
        win.title = newName;
    }

    void Window::updateSize()
    {
        SDL_GetWindowSize(getSDL(), &win.size_x, &win.size_y);
    }

    void Window::onEvent(SDL_Event* ev)
    {
        switch(ev -> window.event)
        {
            case SDL_WINDOWEVENT_SIZE_CHANGED:
                Window::updateSize();
                Graphics::update();
                break;

            // Repaint on exposure
            case SDL_WINDOWEVENT_EXPOSED:
                Graphics::update();
                break;

            case SDL_WINDOWEVENT_MINIMIZED:
                win.minimized = true;
                break;

            case SDL_WINDOWEVENT_MAXIMIZED:
                win.minimized = false;
                break;

            case SDL_WINDOWEVENT_RESTORED:
                win.minimized = false;
                break;
        }
    }

    void Window::setFullscreen(uint32_t flags)
    {
    #ifdef BUILD_TYPE_VITA
        // TODO: Warning or log or something because only fullscreen is allowed
    #else
        // Save flags if valid
        if(flags == 0 || flags == SDL_WINDOW_FULLSCREEN || flags == SDL_WINDOW_FULLSCREEN_DESKTOP)
        {
            win.fullscreen_type = flags;
            win.fullscreen = !(flags == 0);
            SDL_SetWindowFullscreen(getSDL(), flags);
        }
    #endif
    }

    void Window::free()
    {
        if(win.window != nullptr)
        {
            SDL_DestroyWindow(win.window);
            win.window = nullptr;
        }
    }

    #undef win
}