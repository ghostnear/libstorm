#include "graphics.hpp"

namespace Storm
{
    Graphics::Graphics()
    {
        // Renderer flags
        uint32_t flags = 0;

        // SDL renderer
        renderer = SDL_CreateRenderer(Window::getSDL(), -1, flags);
        if(renderer == nullptr)
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
}