#pragma once

#include "../Graphics.hpp"

using namespace Storm;

// Wrapper class over SDL_Texture so it can be used as a component.
// Added bonus: automatic freeing.
class Texture
{
private:
    SDL_Texture* textureData = NULL;

public:
    SDL_Texture* get();
    
    Texture(SDL_Texture*);
    ~Texture();
};
