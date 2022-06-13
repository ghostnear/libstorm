#include "libstorm.hpp"

namespace Storm
{
    void showSimpleMessageBox(std::string title, std::string message, MessageBoxType type, SDL_Window* parent)
    {
        // Convert the type from Storm to SDL
        uint32_t flags = 0;
        switch(type)
        {
            case MessageBoxType::ERROR:
                flags = SDL_MESSAGEBOX_ERROR;
                break;
            case MessageBoxType::WARNING:
                flags = SDL_MESSAGEBOX_WARNING;
                break;
            case MessageBoxType::INFO:
                flags = SDL_MESSAGEBOX_INFORMATION;
                break;
        }

        // Try to show the message box using SDL, if it is not possible, write to output
        if(SDL_ShowSimpleMessageBox(flags, title.c_str(), message.c_str(), parent) < 0)
            printf("%s!\n%s", title.c_str(), message.c_str());
    }
};