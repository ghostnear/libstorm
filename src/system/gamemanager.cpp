#include "system/gamemanager.hpp"

namespace Storm
{
    void State::assignGameManager(GameManager* gm)
    {
        _gm = gm;
    }

    #define gm GameManager::getInstance()

    GameManager::GameManager()
    {
        _running = true;
        _now =  SDL_GetPerformanceCounter();
    }

    void GameManager::draw()
    {
        // Draw all the states in order
        for(auto i : gm._states)
            i -> draw();
    }

    double GameManager::getDeltaTime()
    {
        return gm._dt;
    }

    void GameManager::update()
    {
        // Update delta time
        gm._last = gm._now;
        gm._now = SDL_GetPerformanceCounter();
        gm._dt = (double)((gm._now - gm._last) / (double)SDL_GetPerformanceFrequency());

        // If no FPS cap just update
        if(gm._fpsLimit < 1)
            for(auto i : gm._states)
                i -> update(gm._dt);
        else
        {
            // Compensate for the time passed if it took too long
            gm._acc += gm._dt;
            while(gm._acc >= 1.0 / gm._fpsLimit)
            {
                gm._dt = 1.0 / gm._fpsLimit;
                for(auto i : gm._states)
                    i -> update(gm._dt);
                gm._acc -= 1.0 / gm._fpsLimit;
            }
            // Sleep till next frame
            std::this_thread::sleep_for(std::chrono::milliseconds((int)(1000 * (1.0 / gm._fpsLimit - gm._acc))));
        }
    }

    GameManager& GameManager::getInstance()
    {
        // This is instantiated on first use and guaranteed to be the only one
        static GameManager instance;
        return instance;
    }

    void GameManager::pushState(State* newState)
    {
        // Make sure the game is not paused
        gm._running = true;

        // Add new state
        newState -> onInit();
        newState -> assignGameManager(&gm);
        gm._states.push_back(newState);
    }

    void GameManager::popState()
    {
        // Remove latest added state and stop if there are no states
        gm._states.pop_back();
        if(gm._states.size() == 0)
            gm._running = false;
    }

    void GameManager::limitFPS(int32_t newLimit)
    {
        gm._fpsLimit = newLimit;
    }

    bool GameManager::isRunning()
    {
        return gm._running;
    }

    #undef gm
};
