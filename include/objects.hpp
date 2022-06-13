#ifndef LIBSTORM_OBJECTS_HPP
#define LIBSTORM_OBJECTS_HPP

#include "deps.hpp"
#include "oop.hpp"
#include "structs.hpp"

namespace Storm
{
    class TextObject : public BaseClass
    {
    public:
        void setString(std::string s)   {   _s = s; rebuild();  }
        std::string getString()         {   return _s;  }

        void setFont(TTF_Font* newFont) {   _font = newFont; rebuild(); }

        void setColor(SDL_Color newC)   {   _color = newC;  rebuild();  }
        void setColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) {   _color = {r, g, b, a};  rebuild();  }

        void setPositionScreenRelative(bool newval) {   positionScreenRelative = newval;    }
        void setSizeScreenRelative(bool newval)     {   sizeScreenRelative = newval;    }

        void onInit() override  {}

        Vec2<double> getPosition()  {   return position;    }
        void setPosition(Vec2<double> newPos) {    position = newPos;    }
        void setPosition(double newX, double newY) {    position = {.x = newX, .y = newY};    }

        Vec2<double> getSize()  {   return size;    }
        void setSize(Vec2<double> newSize) {    size = newSize;    }
        void setSize(double newX, double newY) {    size = {.x = newX, .y = newY};    }

        void setOffset(Vec2<double> newOff) {    offset = newOff;    }
        void setOffset(double newX, double newY) {    offset = {.x = newX, .y = newY};    }

        void onDestroy() override
        {
            if(_renText != nullptr)
                SDL_FreeSurface(_renText), _renText = nullptr;
            if(_texture != nullptr)
                SDL_DestroyTexture(_texture), _texture = nullptr;
        }

        void draw(OOPState* gm) override
        {
            if(_renText != nullptr)
            {
                drawRect.w = (int)(size.x * (sizeScreenRelative ? Window::getSize().first : 1));
                drawRect.h = (int)(size.y * (sizeScreenRelative ? Window::getSize().second : 1));
                drawRect.x = (int)(position.x * (positionScreenRelative ? Window::getSize().first : 1)) - drawRect.w * offset.x;
                drawRect.y = (int)(position.y * (positionScreenRelative ? Window::getSize().second : 1)) - drawRect.h * offset.y;
                SDL_RenderCopy(Graphics::getSDL(), _texture, NULL, &drawRect);
            }
        }

        void update(OOPState* gm, double dt) override   {}

    private:
        Vec2<double> position = {.x = 0, .y = 0}, size = {.x = -1, .y = -1}, offset = {.x = 0, .y = 0};
        SDL_Rect drawRect;
        bool positionScreenRelative = false;
        bool sizeScreenRelative = false;
        SDL_Color _color = {0, 0, 0, 255};
        TTF_Font* _font = nullptr;
        std::string _s = "<null>";
        SDL_Surface* _renText = nullptr;
        SDL_Texture* _texture = nullptr;

        // Rebuilds the text after a font, size or string change
        void rebuild()
        {
            // We can not draw without a font
            if(_font != nullptr)
            {
                onDestroy();
                    
                _renText = TTF_RenderText_Solid(
                    _font,
                    _s.c_str(),
                    _color
                );
                _texture = SDL_CreateTextureFromSurface(Graphics::getSDL(), _renText);
                
                if(size.x < 0 || size.y < 0)
                {
                    int nw, nh;
                    SDL_QueryTexture(_texture, NULL, NULL, &nw, &nh);
                    size = {
                        .x = 1.0 * nw,
                        .y = 1.0 * nh
                    };
                }
            }
            else
            {/* TODO: Logging system or something to show a warning */}
        }
    };
};

#endif