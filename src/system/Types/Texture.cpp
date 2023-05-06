#include "system/Types/Texture.hpp"
#include <SDL2/SDL_render.h>

SDL_Texture* Texture::get()
{
    return textureData;
}

Texture::Texture(SDL_Texture* newTexture)
{
    textureData = newTexture;
}

Texture::~Texture()
{
    if(textureData != nullptr)
        SDL_DestroyTexture(textureData);
}