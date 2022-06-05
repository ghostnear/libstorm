#include "libstorm.hpp"

namespace Storm
{
    int32_t StormInit()
    {
        // Init SDL
        if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
        {
            showSimpleMessageBox(
                "SDL error",
                "An error occured while initialising SDL2:\n" + std::string(SDL_GetError()));
            return EXIT_FAILURE;        
        }

        // Check if window was created corectly
        if(Window::getSDL() == nullptr)
        {
            showSimpleMessageBox(
                "SDL error",
                "An error occured while creating the SDL window:\n" + std::string(SDL_GetError()));
            return EXIT_FAILURE;
        }

        // Check if renderer has been created properly
        if(Graphics::getSDL() == nullptr)
        {
            showSimpleMessageBox(
                "SDL error",
                "An error occured while initialising the graphics system:\n" + std::string(SDL_GetError()));
            return EXIT_FAILURE;            
        }

        return EXIT_SUCCESS;
    }

    int32_t StormQuit()
    {
        // Quit SDL
        SDL_Quit();

        return EXIT_SUCCESS;
    }
}