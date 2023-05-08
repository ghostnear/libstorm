#include "system/AssetTypes/ImageAsset.hpp"
#include "system/Graphics.hpp"

void ImageAsset::load(AssetToLoad metadata)
{
    SDL_Surface* loadedSurface = IMG_Load(metadata.path.c_str());

    // Args are not used yet, just get rid of them.
    if(metadata.args)
        delete (json*)metadata.args;

    // Loading failed, give up.
    if(loadedSurface == NULL)
    {
        Window::show_simple_message_box(
            "An error occured while loading assets!",
            "Image could not be loaded from path: " + metadata.path + "!\nSDL_Error(): " + \
            std::string(SDL_GetError())
        );
        return;
    }

    // Create texture data on the GPU and get rid of the surface as to not keep RAM busy.
    textureData = SDL_CreateTextureFromSurface(Graphics::get_SDL(), loadedSurface);
    SDL_FreeSurface(loadedSurface);

    // Something's wrong, I can feel it.
    if(textureData == NULL)
    {
        Window::show_simple_message_box(
            "An error occured while creating texture!",
            "Texture could not be created from image at path: " + metadata.path + "!\nSDL_Error(): " + \
            std::string(SDL_GetError())
        );
        return;
    }

    SDL_SetTextureBlendMode(textureData, SDL_BLENDMODE_BLEND);
}

SDL_Texture* ImageAsset::get()
{
    return textureData;
}

Vec2<int> ImageAsset::get_size()
{
    int w, h;
    SDL_QueryTexture(textureData, NULL, NULL, &w, &h);
    return Vec2<int>{.x = w, .y = h};
}

ImageAsset::~ImageAsset()
{
    if(textureData != NULL)
        SDL_DestroyTexture(textureData);
}