#ifndef LIBSTORM_WINDOW_HPP
#define LIBSTORM_WINDOW_HPP

#include "deps.hpp"
#include "graphics.hpp"
#include "msgbox.hpp"

namespace Storm
{
    class Graphics;

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

            #define win Window::getInstance()

            // Property getters
            static SDL_Window* getSDL()                 {   return win.window;                              }
            static std::string getName()                {   return win.title;                               }
            static bool shouldClose()                   {   return win.isquit;                              }
            static std::pair<int, int> getSize()        {   return std::make_pair(win.size_x, win.size_y);  }
            static bool isFullscreen()                  {   return win.fullscreen;                          }
            static bool isMinimized()                   {   return win.minimized;                           }
            static void resize(int newX, int newY);
            static void updateSize();
            static void close();
            static void onEvent(SDL_Event* ev);
            static void setName(std::string newName);
            static void setFullscreen(uint32_t flags);
            static void free();

            #undef win

        private:
            // Constructor should be private
            Window();

            // Window properties
            SDL_Window* window = nullptr;
            std::string title = "<window_name>";
            bool isquit = false;
        
            // The Vita has specific requirements
        #ifdef BUILD_TYPE_VITA
            int size_x = 960, size_y = 540;
            uint32_t fullscreen_type = SDL_WINDOW_FULLSCREEN;
            bool fullscreen = true;
            bool minimized = false;
        #else
            int size_x = 540, size_y = 540;
            uint32_t fullscreen_type = 0;
            bool minimized = false;
            bool fullscreen = false;
        #endif 
    };
}

#endif