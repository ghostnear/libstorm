#ifndef LIBSTORM_GRAPHICS_HPP
#define LIBSTORM_GRAPHICS_HPP

#include "deps.hpp"
#include "window.hpp"

namespace Storm
{
    class Window;

    // Graphics singleton
    // https://stackoverflow.com/questions/1008019/c-singleton-design-pattern
    class Graphics
    {
        public:
            // Do not allow for multiple instances
            Graphics(Graphics const&)       = delete;
            void operator=(Graphics const&) = delete;

            // Methods
            static SDL_Renderer* getSDL();
            static Graphics& getInstance();
            static void setColor(SDL_Color c);
            static void setColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);
            static void clear();
            static void clear(SDL_Color c);
            static void clear(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);
            static void update();
            static void free();

        private:
            // Constructor should be private
            Graphics();

            // Properties
            SDL_Renderer* _r = nullptr;
    };
}

#endif
