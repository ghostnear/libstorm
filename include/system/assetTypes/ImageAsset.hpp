#ifndef LIBSTORM_ASSETS_IMAGE_HPP
#define LIBSTORM_ASSETS_IMAGE_HPP

#include "../AssetManager.hpp"

using namespace Storm;

class ImageAsset : public Asset
{
public:
    void load(AssetToLoad metadata) override;
};

#endif