#pragma once

#include "deps.hpp"

namespace Storm
{
    class Graphics;

    // Window singleton as there is only one window ever
    // https://stackoverflow.com/questions/1008019/c-singleton-design-pattern
    class Window
    {
        private:
            // Constructor should be private
            Window();

            // Window properties
            SDL_Window* window = nullptr;
            std::string title = "<libstorm_window>";
            bool isQuit = false;

            // Different screen configs per build platform.
            // TODO: replace with platform-specific configs.
        #ifdef VITA
            // 960 x 544 screen, fullscreen
            Vec2<int> size {
                .x = 960,
                .y = 544
            };
            uint32_t fullscreenType = SDL_WINDOW_FULLSCREEN;
            bool fullscreen = true;
            bool minimized = false;
        #else
            // 960 x 540 screen, half of 1080p, no fullscreen
            Vec2<int> size {
                .x = 960,
                .y = 540
            };
            uint32_t fullscreenType = 0;
            bool minimized = false;
            bool fullscreen = false;
        #endif

        public:
            // Do not allow for multiple instances
            Window(Window const&)          = delete;
            void operator=(Window const&)  = delete;
            
            // Not necesarely related to the window itself, but similar meaning.
            static void show_simple_message_box(std::string title, std::string message, SDL_MessageBoxFlags type = SDL_MESSAGEBOX_ERROR);

            // Window methods
            static Window& get_instance();
            static SDL_Window* get_SDL();
            static std::string get_name();
            static bool should_close();
            static Vec2<int> get_size();
            static bool is_fullscreen();
            static bool is_minimized();
            static void update_size();
            static void set_size(Vec2<int> newSize);
            static void on_event(SDL_Event* ev);
            static void set_name(std::string newName);
            static void set_fullscreen(uint32_t flags);
            static void close();
            static void free();
    };
}
