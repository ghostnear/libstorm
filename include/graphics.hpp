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
            // Get the input instance
            static Graphics& getInstance()
            {
                // This is instantiated on first use and guaranteed to be the only one
                static Graphics instance;
                return instance;
            }

            // Do not allow for multiple instances
            Graphics(Graphics const&)          = delete;
            void operator=(Graphics const&)  = delete;

            // Getters
            static SDL_Renderer* getSDL()     {   return Graphics::getInstance()._r;    }

            // Methods
            static void update();
            static void setColor(int r, int g, int b, int a = 255);
            static void setColor(SDL_Color c);
            static void clear();
            static void clear(int r, int g, int b, int a = 255);
            static void clear(SDL_Color c);
            static void free();

        private:
            // Constructor should be private
            Graphics();

            // Properties
            SDL_Renderer* _r = nullptr;
    };
}

#endif