#pragma once

#include "deps.hpp"

namespace Storm
{
    class Window;

    // Graphics singleton
    // https://stackoverflow.com/questions/1008019/c-singleton-design-pattern
    class Graphics
    {
        private:
            // Constructor should be private
            Graphics();

            // Properties
            SDL_Renderer* _r = nullptr;
            bool vsync = false;

        public:
            // Do not allow for multiple instances
            Graphics(Graphics const&)       = delete;
            void operator=(Graphics const&) = delete;

            // Methods
            static SDL_Renderer* get_SDL();
            static Graphics& get_instance();
            static void set_color(SDL_Color c);
            static void set_color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);
            static void clear();
            static void clear(SDL_Color c);
            static void clear(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);
            static void update();
            static void free();
            static void toggle_vsync();
    };
}
