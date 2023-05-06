#include "system/Window.hpp"
#include "system/Graphics.hpp"

namespace Storm
{
    #define win Window::get_instance()

    void Window::show_simple_message_box(std::string title, std::string message, SDL_MessageBoxFlags type)
    {
        // Try to show the message box using SDL, if it is not possible, write to output.
        if(SDL_ShowSimpleMessageBox(type, title.c_str(), message.c_str(), win.get_SDL()) < 0)
            printf("%s!\n%s", title.c_str(), message.c_str());
    }

    Window::Window()
    {
        // Window flags
        // TODO: replace these with an actual config file
        uint32_t flags =  fullscreenType;

        // Create the SDL window
        window = SDL_CreateWindow(
            title.c_str(),
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            size.x, size.y,
            flags);
        if(window == nullptr)
            isQuit = true;
    }

    Window& Window::get_instance()
    {
        // This is instantiated on first use and guaranteed to be the only one
        static Window instance;
        return instance;
    }

    SDL_Window* Window::get_SDL()
    {
        return win.window;
    }

    std::string Window::get_name()
    {
        return win.title;
    }

    bool Window::should_close()
    {
        return win.isQuit;
    }

    bool Window::is_fullscreen()
    {
        return win.fullscreen;
    }

    bool Window::is_minimized()
    {
        return win.minimized;
    }

    Vec2<int> Window::get_size()
    {
        return win.size;
    }

    void Window::update_size()
    {
        SDL_GetWindowSize(get_SDL(), &win.size.x, &win.size.y);
    }

    void Window::on_event(SDL_Event* ev)
    {
        switch(ev->window.event)
        {
#ifndef VITA
            // If window changed for any reason, resize and repaint
            case SDL_WINDOWEVENT_EXPOSED:
            case SDL_WINDOWEVENT_SIZE_CHANGED:
                Window::update_size();
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
                update_size();
                win.minimized = false;
                break;
#endif
        }
    }

    void Window::set_name(std::string newName)
    {
        SDL_SetWindowTitle(get_SDL(), newName.c_str());
        win.title = newName;
    }

    void Window::set_fullscreen(uint32_t flags)
    {
    #ifndef VITA
        // Save flags if valid
        if(flags == 0 || flags == SDL_WINDOW_FULLSCREEN || flags == SDL_WINDOW_FULLSCREEN_DESKTOP)
        {
            win.fullscreenType = flags;
            win.fullscreen = !(flags == 0);
            SDL_SetWindowFullscreen(get_SDL(), flags);
            update_size();
        }
    #endif
    }

    void Window::set_size(Vec2<int> newSize)
    {
        SDL_SetWindowSize(get_SDL(), newSize.x, newSize.y);
        update_size();
    }

    void Window::close()
    {
        win.isQuit = true;
        SDL_DestroyWindow(get_SDL());
    }

    void Window::free()
    {
        // If window has not been destroyed yet, do it now
        if(win.window != nullptr)
            SDL_DestroyWindow(win.window), win.window = nullptr;
    }

    #undef win
}
