#include "libStorm.hpp"

// Major TODOs:
// TODO: optimise compiling speed by fixing the header inclusion mess
// TODO: optimise performance (will never be fully cleared as there is always something to optimise)

namespace Storm
{
    int32_t StormInit()
    {
        // Init SDL.
        if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
        {
            show_simple_message_box(
                "SDL2 error",
                "An error occured while initialising SDL2:\n" + std::string(SDL_GetError())
            );
            StormQuit(-1);
        }

        if(TTF_Init() < 0)
        {
            show_simple_message_box(
                "SDL2_ttf error",
                "An error occured while initialising SDL2_ttf:\n" + std::string(TTF_GetError())
            );
            StormQuit(-1);
        }

        int32_t img_flags = IMG_INIT_PNG;
        if(!(IMG_Init(img_flags) & img_flags))
        {
            show_simple_message_box(
                "SDL2_img error",
                "An error occured while initialising SDL2_img:\n" + std::string(IMG_GetError())
            );
            StormQuit(-1);
        }

        // Check if window was created correctly.
        if(Window::get_SDL() == nullptr)
        {
            show_simple_message_box(
                "SDL2 error",
                "An error occured while creating the SDL2 window:\n" + std::string(SDL_GetError())
            );
            StormQuit(-1);
        }

        // Check if renderer has been created correctly.
        if(Graphics::get_SDL() == nullptr)
        {
            show_simple_message_box(
                "SDL2 error",
                "An error occured while initialising the graphics system:\n" + std::string(SDL_GetError())
            );
            StormQuit(-1);
        }

        return EXIT_SUCCESS;
    }

    int32_t StormQuit(int32_t ret_val)
    {
        // Free everything memory related here.
        Graphics::free();
        Window::free();

        // Quit SDL.
        IMG_Quit();
        TTF_Quit();
        SDL_Quit();

    #ifdef VITA
        // Tell the kernel the process has been exited.
        sceKernelExitProcess(ret_val);
    #endif

        // Any return value that is not 0 is an error.
        return (ret_val == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
    }
}
