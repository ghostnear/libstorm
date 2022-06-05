#include "window.hpp"

namespace Storm
{
    Window::Window()
    {
        // Window flags
        uint32_t flags = 0;

        // If window can be in vulkan mode, add the flag
        if(SDL_Vulkan_LoadLibrary(nullptr) != -1)
        {   flags |= SDL_WINDOW_VULKAN; SDL_Vulkan_UnloadLibrary();  }
        else
            flags |= SDL_WINDOW_OPENGL;

        // Create the SDL window
        window = SDL_CreateWindow(
            title.c_str(),
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            960, 540,
            flags);
    }
}