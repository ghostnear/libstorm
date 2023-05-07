#include "system/AssetTypes/AnimationAsset.hpp"
#include "system/Graphics.hpp"

void AnimationAsset::load(AssetToLoad metadata)
{
    json* args = (json*)metadata.args;

    for(auto frameData : (*args))
    {
        if(frameData.is_string())
        {
            ImageAsset* frame = new ImageAsset();
            frame->load(
                AssetToLoad(
                    AssetType::Image,
                    "",
                    metadata.path + frameData.get<std::string>(),
                    nullptr
                )
            );
            
            this->frameData.push_back(frame);
        }
    }
}

std::size_t AnimationAsset::get_frame_count()
{
    return frameData.size();
}

ImageAsset* AnimationAsset::get_frame(std::size_t frame)
{
    return frameData[frame];
}

AnimationAsset::~AnimationAsset()
{
    for(auto frame : frameData)
        delete frame;
}