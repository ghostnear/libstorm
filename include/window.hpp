#ifndef LIBSTORM_WINDOW_HPP
#define LIBSTORM_WINDOW_HPP

#include "deps.hpp"
#include "msgbox.hpp"

namespace Storm
{
    // Window singleton as there is only one window ever
    // https://stackoverflow.com/questions/1008019/c-singleton-design-pattern
    class Window
    {
        public:
            // Get the window instance
            static Window& getInstance()
            {
                // This is instantiated on first use and guaranteed to be the only one
                static Window instance;
                return instance;
            }

            // Do not allow for multiple instances
            Window(Window const&)          = delete;
            void operator=(Window const&)  = delete;

            // Property getters
            static SDL_Window* getSDL()                 {   return Window::getInstance().window;    }
            static std::string getName()                {   return Window::getInstance().title;     }
            static bool shouldClose()                   {   return Window::getInstance().isquit;    }
            static void close();
            static void setName(std::string newName);
            static bool isFullscreen()      {   return Window::getInstance().fullscreen;}
            static void setFullscreen(uint32_t flags);

        private:
            // Constructor should be private
            Window();

            // Window properties
            SDL_Window* window = nullptr;
            std::string title = "<window_name>";
            bool isquit = false;
            uint32_t fullscreen_type = 0;
            bool fullscreen = false;
    };
}

#endif