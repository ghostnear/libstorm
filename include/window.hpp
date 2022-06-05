#ifndef LIBSTORM_WINDOW_HPP
#define LIBSTORM_WINDOW_HPP

#include "deps.hpp"
#include "msgbox.hpp"
#include <SDL2/SDL_vulkan.h>

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
            static SDL_Window* getSDL()
            {
                return Window::getInstance().window;
            }

        private:
            // Constructor should be private
            Window();

            // Window properties
            SDL_Window* window = nullptr;
            std::string title = "<null>";
    };
}

#endif