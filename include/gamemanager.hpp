#ifndef LIBSTORM_GAME_MANAGER_HPP
#define LIBSTORM_GAME_MANAGER_HPP

#include "deps.hpp"
#include <vector>

namespace Storm
{
    class GameManager;

    class State
    {
    public:
        virtual void onInit() = 0;
        virtual void onDestroy() = 0;
        virtual void draw(GameManager* gm) = 0;
        virtual void update(GameManager* gm, double dt) = 0;
    };

    class GameManager
    {
    public:
        GameManager();

        // Methods
        void draw();
        void update(double dt);
        void pushState(State* newState);

    private:
        std::vector<State*> _states;
        bool _running = false;
    };
};

#endif