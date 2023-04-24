#ifndef LIBSTORM_ASSETS_IMAGE_HPP
#define LIBSTORM_ASSETS_IMAGE_HPP

#include "../AssetManager.hpp"
#include <SDL2/SDL_render.h>

using namespace Storm;

class ImageAsset : public Asset
{
private:
    SDL_Texture* textureData = NULL;

public:
    ~ImageAsset();

    SDL_Texture* get();

    void load(AssetToLoad metadata) override;
};

#endif