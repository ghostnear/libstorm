#include "system/AssetTypes/FontAsset.hpp"

void FontAsset::load(AssetToLoad metadata)
{
    _path = metadata.path;
    if(metadata.args)
    {
        json* args = (json*)metadata.args;
        
        // No sizes are loaded yet so getting should load them on the fly.
        if((*args)["sizes"].is_array())
            for(auto x : (*args)["sizes"])
                get(x);
            
        delete args;
    }
}

FontAsset::~FontAsset()
{
    freeAll();
}

TTF_Font* FontAsset::get(size_t size)
{
    // If it exists, perfect
    if(_f[size])
        return _f[size];

    // Load the font from the path
    _f[size] = TTF_OpenFont(_path.c_str(), size);

    // Something's gone wrong.
    if(!_f[size])
        Window::show_simple_message_box("Error", "Could not load font at path: " + _path + "\nWith size: " + Utils::to_string<size_t>(size) + "\nTTF_Error(): " + TTF_GetError(), SDL_MESSAGEBOX_ERROR);

    return _f[size];
}

void FontAsset::free(size_t size)
{
    // Don't delete an inexistent font.
    if(!_f[size])
        return;

    TTF_CloseFont(_f[size]);
    _f[size] = nullptr;
}

void FontAsset::freeAll()
{
    for(auto x : _f)
        free(x.first);
}