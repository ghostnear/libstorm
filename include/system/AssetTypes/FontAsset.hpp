#pragma once

#include "../AssetManager.hpp"

using namespace Storm;

class FontAsset : public Asset
{
private:
    std::string _path;
    std::map<size_t, TTF_Font*> _f;

public:
    ~FontAsset();

    void load(AssetToLoad metadata) override;

    // Gets the font for a specific size.
    TTF_Font* get(size_t size);

    // Frees all sizes.
    void freeAll();

    // Frees one size.
    void free(size_t size);
};