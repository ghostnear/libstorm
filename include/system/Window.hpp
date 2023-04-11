#ifndef LIBSTORM_WINDOW_HPP
#define LIBSTORM_WINDOW_HPP

#include "deps.hpp"

namespace Storm
{
    class Graphics;

    void showSimpleMessageBox(std::string title, std::string message, SDL_MessageBoxFlags type = SDL_MESSAGEBOX_ERROR, SDL_Window* parent = nullptr);

    // Window singleton as there is only one window ever
    // https://stackoverflow.com/questions/1008019/c-singleton-design-pattern
    class Window
    {
        public:
            // Do not allow for multiple instances
            Window(Window const&)          = delete;
            void operator=(Window const&)  = delete;

            // Window methods
            static Window& getInstance();
            static SDL_Window* getSDL();
            static std::string getName();
            static bool shouldClose();
            static Vec2<int> getSize();
            static bool isFullscreen();
            static bool isMinimized();
            static void updateSize();
            static void onEvent(SDL_Event* ev);
            static void setName(std::string newName);
            static void setFullscreen(uint32_t flags);
            static void close();
            static void free();

        private:
            // Constructor should be private
            Window();

            // Window properties
            SDL_Window* window = nullptr;
            std::string title = "<libstorm_window>";
            bool isquit = false;

            // Different screen configs per build platform
        #ifdef BUILD_TYPE_VITA
            // 960 x 544 screen, fullscreen
            Vec2<int> size {
                .x = 960,
                .y = 544
            };
            uint32_t fullscreen_type = SDL_WINDOW_FULLSCREEN;
            bool fullscreen = true;
            bool minimized = false;
        #else
            // 960 x 540 screen, no fullscreen
            Vec2<int> size {
                .x = 960,
                .y = 540
            };
            uint32_t fullscreen_type = 0;
            bool minimized = false;
            bool fullscreen = false;
        #endif
    };
}

#endif
