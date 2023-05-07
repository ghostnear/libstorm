#pragma once

#include "../AssetManager.hpp"

using namespace Storm;

class ImageAsset : public Asset
{
private:
    SDL_Texture* textureData = NULL;

public:
    virtual ~ImageAsset();

    SDL_Texture* get();

    void load(AssetToLoad metadata) override;
};
