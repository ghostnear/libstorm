#include "gamemanager.hpp"

namespace Storm
{
    GameManager::GameManager()
    {
        _running = true;
    }

    void GameManager::draw()
    {
        for(auto i : _states)
            i -> draw(this);
    }

    void GameManager::update(double dt)
    {
        for(auto i : _states)
            i -> update(this, dt);
    }

    void GameManager::pushState(State* newState)
    {
        newState -> onInit();
        _states.push_back(newState);
    }
};