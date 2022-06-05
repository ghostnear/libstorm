#include "libstorm.hpp"

namespace Storm
{
    int32_t Storm_Init()
    {
        // Init SDL
        if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
        {
            showSimpleMessageBox(
                "SDL error",
                "An error occured while initialising SDL2: " + std::string(SDL_GetError()));
            return EXIT_FAILURE;        
        }

        return EXIT_SUCCESS;
    }

    int32_t Storm_Quit()
    {
        // Quit SDL
        SDL_Quit();

        return EXIT_SUCCESS;
    }
}