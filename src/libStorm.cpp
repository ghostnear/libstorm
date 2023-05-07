#include "libStorm.hpp"

namespace Storm
{
    int32_t StormInit()
    {
        // Init SDL.
        if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
        {
            Window::show_simple_message_box(
                "SDL2 error",
                "An error occured while initialising SDL2:\n" + std::string(SDL_GetError())
            );
            StormQuit(-1);
        }

        if(TTF_Init() < 0)
        {
            Window::show_simple_message_box(
                "SDL2_ttf error",
                "An error occured while initialising SDL2_ttf:\n" + std::string(TTF_GetError())
            );
            StormQuit(-1);
        }

        int32_t img_flags = IMG_INIT_PNG;
        if(!(IMG_Init(img_flags) & img_flags))
        {
            Window::show_simple_message_box(
                "SDL2_img error",
                "An error occured while initialising SDL2_img:\n" + std::string(IMG_GetError())
            );
            StormQuit(-1);
        }

        // Check if window was created correctly.
        if(Window::get_SDL() == nullptr)
        {
            Window::show_simple_message_box(
                "SDL2 error",
                "An error occured while creating the SDL2 window:\n" + std::string(SDL_GetError())
            );
            StormQuit(-1);
        }

        // Check if renderer has been created correctly.
        if(Graphics::get_SDL() == nullptr)
        {
            Window::show_simple_message_box(
                "SDL2 error",
                "An error occured while initialising the graphics system:\n" + std::string(SDL_GetError())
            );
            StormQuit(-1);
        }

        return EXIT_SUCCESS;
    }

    int32_t StormQuit(int32_t returnValue)
    {
        // Free all states.
        GameManager::pop_all_states();

        // Free everything memory related here.
        Graphics::free();
        Window::free();

        // Quit SDL.
        IMG_Quit();
        TTF_Quit();
        SDL_Quit();

    #ifdef VITA
        // Tell the kernel the process has been exited.
        sceKernelExitProcess(returnValue);
    #endif

        // Any return value that is not 0 is an error.
        return (returnValue == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
    }

    int32_t StormMainLoop()
    {
        while(!Window::should_close() && GameManager::is_running())
        {
            // Poll events
            Input::pollEvents();

            // Update
            GameManager::update();

            // Draw
            if(!Window::is_minimized())
                GameManager::draw();
            
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }

        // Quit and return the quit result
        return StormQuit(EXIT_SUCCESS);
    }
}
