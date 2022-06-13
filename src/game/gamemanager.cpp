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
            i -> draw();
    }

    void GameManager::update()
    {
        gm._last = gm._now;
        gm._now = SDL_GetPerformanceCounter();
        gm._dt = (double)((gm._now - gm._last) / (double)SDL_GetPerformanceFrequency());
        for(auto i : gm._states)
            i -> update(gm._dt);
    }

    void GameManager::pushState(State* newState)
    {
        gm._running = true;
        newState -> onInit();
        newState -> assignGameManager(&gm);
        gm._states.push_back(newState);
    }

    void GameManager::popState()
    {
        gm._states.pop_back();
        if(gm._states.size() == 0)
            gm._running = false;
    }

    double GameManager::getFPS()
    {
        return 1.0 / gm._dt;
    }

    #undef gm
};