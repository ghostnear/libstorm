#include "systems.hpp"

namespace Storm
{
    void TextSystem::draw(World* w)
    {
        for (auto const& entity : _entities)
        {
            auto& tcomponent = w -> getComponent<Text>(entity);
            SDL_Color c;
            c.r = 255;
            c.g = 255;
            c.b = 255;
            c.a = 255;
            SDL_Surface* fontSurface = TTF_RenderText_Solid(
                tcomponent.font,
                tcomponent.str.c_str(),
                c
            );

            SDL_Texture* fontTexture = SDL_CreateTextureFromSurface(Graphics::getSDL(), fontSurface);

            SDL_RenderCopy(Graphics::getSDL(), fontTexture, NULL, NULL);
            
            SDL_FreeSurface(fontSurface);
            SDL_DestroyTexture(fontTexture);
        }
    }

    void TextSystem::update(World* w, double dt) { }
};