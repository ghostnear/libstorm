#include "system/Window.hpp"
#include "system/Graphics.hpp"

namespace Storm
{
    void showSimpleMessageBox(std::string title, std::string message, SDL_MessageBoxFlags type, SDL_Window* parent)
    {
        // Try to show the message box using SDL, if it is not possible, write to output.
        if(SDL_ShowSimpleMessageBox(type, title.c_str(), message.c_str(), parent) < 0)
            printf("%s!\n%s", title.c_str(), message.c_str());
    }

    #define win Window::getInstance()

    Window::Window()
    {
        // Window flags
        // TODO: replace these with an actual config file
        uint32_t flags = SDL_WINDOW_RESIZABLE | fullscreen_type;

        // Create the SDL window
        window = SDL_CreateWindow(
            title.c_str(),
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            size.x, size.y,
            flags);
        if(window == nullptr)
            isquit = true;
    }

    Window& Window::getInstance()
    {
        // This is instantiated on first use and guaranteed to be the only one
        static Window instance;
        return instance;
    }

    SDL_Window* Window::getSDL()
    {
        return win.window;
    }

    std::string Window::getName()
    {
        return win.title;
    }

    bool Window::shouldClose()
    {
        return win.isquit;
    }

    bool Window::isFullscreen()
    {
        return win.fullscreen;
    }

    bool Window::isMinimized()
    {
        return win.minimized;
    }

    Vec2<int> Window::getSize()
    {
        return win.size;
    }

    void Window::updateSize()
    {
        SDL_GetWindowSize(getSDL(), &win.size.x, &win.size.y);
    }

    void Window::onEvent(SDL_Event* ev)
    {
        switch(ev->window.event)
        {
            // If size changed for any reason, resize and repaint
            case SDL_WINDOWEVENT_SIZE_CHANGED:
                Window::updateSize();
                Graphics::update();
                break;

            // Repaint on exposure
            case SDL_WINDOWEVENT_EXPOSED:
                Window::updateSize();
                Graphics::update();
                break;

            // Minimisation handling to not allow for useless repaints
            case SDL_WINDOWEVENT_MINIMIZED:
                win.minimized = true;
                break;
            case SDL_WINDOWEVENT_MAXIMIZED:
                win.minimized = false;
                break;
            case SDL_WINDOWEVENT_RESTORED:
                Window::updateSize();
                win.minimized = false;
                break;
        }
    }

    void Window::setName(std::string newName)
    {
        SDL_SetWindowTitle(getSDL(), newName.c_str());
        win.title = newName;
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
            Window::updateSize();
        }
    #endif
    }

    void Window::close()
    {
        win.isquit = true;
        SDL_DestroyWindow(getSDL());
    }

    void Window::free()
    {
        // If window has not been destroyed yet, do it now
        if(win.window != nullptr)
            SDL_DestroyWindow(win.window), win.window = nullptr;
    }

    #undef win
}
