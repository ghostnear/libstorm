#ifndef LIBSTORM_SIMPLE_MESSAGE_BOX_HPP
#define LIBSTORM_SIMPLE_MESSAGE_BOX_HPP

namespace Storm
{
    enum MessageBoxType
    {
        ERROR = 0,
        WARNING,
        INFO
    };

    void showSimpleMessageBox(std::string title, std::string message, MessageBoxType type = MessageBoxType::ERROR, SDL_Window* parent = nullptr);
};

#endif