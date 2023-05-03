#include "system/Graphics.hpp"
#include "system/Window.hpp"
#include <SDL2/SDL_render.h>

namespace Storm
{
    #define gfx Graphics::get_instance()

    Graphics::Graphics()
    {
        // Renderer flags
        // TODO: replace these with an actual engine config file
        uint32_t flags = SDL_RENDERER_ACCELERATED;

        // SDL renderer
        _r = SDL_CreateRenderer(Window::get_SDL(), -1, flags);
        if(_r == nullptr)
            Window::close();
    }

    SDL_Renderer* Graphics::get_SDL()
    {
        return Graphics::get_instance()._r;
    }

    Graphics& Graphics::get_instance()
    {
        // This is instantiated on first use and guaranteed to be the only one
        static Graphics instance;
        return instance;
    }

    void Graphics::set_color(SDL_Color c)
    {
        SDL_SetRenderDrawColor(get_SDL(), c.r, c.g, c.b, c.a);
    }

    void Graphics::set_color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
    {
        SDL_SetRenderDrawColor(get_SDL(), r, g, b, a);
    }

    void Graphics::clear()
    {
        SDL_RenderClear(get_SDL());
    }

    void Graphics::clear(SDL_Color c)
    {
        set_color(c);
        clear();
    }

    void Graphics::clear(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
    {
        set_color(r, g, b, a);
        clear();
    }

    void Graphics::update()
    {
        SDL_RenderPresent(get_SDL());
    }

    void Graphics::toggle_vsync()
    {
        gfx.vsync = !gfx.vsync;
        SDL_RenderSetVSync(gfx._r, gfx.vsync);
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
