#include "libstorm.hpp"

namespace Storm
{
    int32_t StormInit()
    {
        // Init SDL
        if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
        {
            showSimpleMessageBox(
                "SDL2 error",
                "An error occured while initialising SDL2:\n" + std::string(SDL_GetError()));
            StormQuit(-1);
        }

        if(TTF_Init() < 0)
        {
            showSimpleMessageBox(
                "SDL2_ttf error",
                "An error occured while initialising SDL2_ttf:\n" + std::string(TTF_GetError()));
            StormQuit(-1);       
        }

        int32_t img_flags = IMG_INIT_PNG;
        if(!(IMG_Init(img_flags) & img_flags))
        {
            showSimpleMessageBox(
                "SDL2_img error",
                "An error occured while initialising SDL2_img:\n" + std::string(IMG_GetError()));
            StormQuit(-1);        
        }

        // Check if window was created corectly
        if(Window::getSDL() == nullptr)
        {
            showSimpleMessageBox(
                "SDL2 error",
                "An error occured while creating the SDL2 window:\n" + std::string(SDL_GetError()));
            StormQuit(-1);
        }

        // Check if renderer has been created properly
        if(Graphics::getSDL() == nullptr)
        {
            showSimpleMessageBox(
                "SDL2 error",
                "An error occured while initialising the graphics system:\n" + std::string(SDL_GetError()));
            StormQuit(-1);       
        }

        return EXIT_SUCCESS;
    }

    int32_t StormQuit(int32_t ret_val)
    {
        Graphics::free();
        Window::free();

        // Quit SDL
        IMG_Quit();
        TTF_Quit();
        SDL_Quit();

        #ifdef BUILD_TYPE_VITA
            sceKernelExitProcess(ret_val);
        #endif
        return (ret_val == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
    }
}