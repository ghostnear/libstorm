#include "gamemanager.hpp"

namespace Storm
{
    #define gm GameManager::getInstance()

    GameManager::GameManager()
    {
        _running = true;
        _now =  SDL_GetPerformanceCounter();
    }

    void GameManager::draw()
    {
        for(auto i : gm._states)
            i -> draw(&gm);
    }

    void GameManager::update()
    {
        gm._last = gm._now;
        gm._now = SDL_GetPerformanceCounter();
        gm._dt = (double)((gm._now - gm._last) / (double)SDL_GetPerformanceFrequency());
        for(auto i : gm._states)
            i -> update(&gm, gm._dt);
    }

    void GameManager::pushState(State* newState)
    {
        newState -> onInit();
        gm._states.push_back(newState);
    }

    double GameManager::getFPS()
    {
        return 1.0 / gm._dt;
    }

    #undef gm
};