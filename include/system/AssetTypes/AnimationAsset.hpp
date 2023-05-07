#pragma once

#include "ImageAsset.hpp"
#include "../AssetManager.hpp"

using namespace Storm;

// This is akin of a collection of frames more than a tilemap-based animation.
// For that, use the (TODO) nonexistent TilemapAsset.

class AnimationAsset : public Asset
{
private:
    std::vector<ImageAsset*> frameData;

public:
    ~AnimationAsset();

    ImageAsset* get_frame(std::size_t frame);

    std::size_t get_frame_count();

    void load(AssetToLoad metadata) override;
};
