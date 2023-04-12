#ifndef LIBSTORM_ASSETS_FONT_HPP
#define LIBSTORM_ASSETS_FONT_HPP

#include "../AssetManager.hpp"

using namespace Storm;

class FontAsset : public Asset
{
public:
    void load(AssetToLoad metadata) override;

    // Gets the font for a specific size.
    TTF_Font* get(size_t size);

    // Frees all sizes.
    void freeAll();

    // Frees one size.
    void free(size_t size);

private:
    std::string _path;
    std::map<size_t, TTF_Font*> _f;
};

#endif