#include "system/graphics.hpp"

namespace Storm
{
    #define gfx Graphics::getInstance()

    Graphics::Graphics()
    {
        // Renderer flags
        // TODO: replace these with an actual config file
        uint32_t flags = SDL_RENDERER_ACCELERATED;

        // SDL renderer
        _r = SDL_CreateRenderer(Window::getSDL(), -1, flags);
        if(_r == nullptr)
            Window::close();
    }

    SDL_Renderer* Graphics::getSDL()
    {
        return Graphics::getInstance()._r;
    }

    Graphics& Graphics::getInstance()
    {
        // This is instantiated on first use and guaranteed to be the only one
        static Graphics instance;
        return instance;
    }

    void Graphics::setColor(SDL_Color c)
    {
        SDL_SetRenderDrawColor(getSDL(), c.r, c.g, c.b, c.a);
    }

    void Graphics::setColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
    {
        SDL_SetRenderDrawColor(getSDL(), r, g, b, a);
    }

    void Graphics::clear()
    {
        SDL_RenderClear(getSDL());
    }

    void Graphics::clear(SDL_Color c)
    {
        setColor(c);
        clear();
    }

    void Graphics::clear(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
    {
        setColor(r, g, b, a);
        clear();
    }

    void Graphics::update()
    {
        SDL_RenderPresent(getSDL());
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