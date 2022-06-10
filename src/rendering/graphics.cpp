#include "graphics.hpp"

namespace Storm
{
    #define gfx Graphics::getInstance()

    Graphics::Graphics()
    {
        // Renderer flags
        uint32_t flags = SDL_RENDERER_ACCELERATED;

        // SDL renderer
        _r = SDL_CreateRenderer(Window::getSDL(), -1, flags);
        if(_r == nullptr)
            Window::close();
    }

    void Graphics::update()
    {
        SDL_RenderPresent(getSDL());
    }

    void Graphics::clear(int r, int g, int b, int a)
    {
        SDL_SetRenderDrawColor(getSDL(), r, g, b, a);
        SDL_RenderClear(getSDL());
    }

    void Graphics::clear(SDL_Color c)
    {
        SDL_RenderClear(getSDL());
    }

    void Graphics::free()
    {
        if(gfx._r != nullptr)
        {
            SDL_DestroyRenderer(gfx._r);
            gfx._r = nullptr;
        }
    }

    #undef gfx
}