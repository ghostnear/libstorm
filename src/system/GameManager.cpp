#include "system/GameManager.hpp"

namespace Storm
{
    #define gm GameManager::get_instance()

    GameManager::GameManager()
    {
        _running = true;
        _now =  SDL_GetPerformanceCounter();
    }

    void GameManager::draw()
    {
        // Draw all the states in order
        for(auto i : gm._states)
            i->draw();
    }

    double GameManager::get_delta_time()
    {
        return gm._dt;
    }

    void GameManager::update()
    {
        // Update delta time
        gm._last = gm._now;
        gm._now = SDL_GetPerformanceCounter();
        gm._dt = (double)((gm._now - gm._last) / (double)SDL_GetPerformanceFrequency());

        // If no FPS cap just update, don't care what happens.
        if(gm._fpsLimit < 1)
            for(auto i : gm._states)
                i->update(gm._dt);
        else
        {
            // Compensate for the time passed if it took too long
            gm._acc += gm._dt;
            while(gm._acc >= 1.0 / gm._fpsLimit)
            {
                gm._dt = 1.0 / gm._fpsLimit;
                for(auto state : gm._states)
                    state->update(gm._dt);
                gm._acc -= 1.0 / gm._fpsLimit;
            }

            // Sleep till next frame
            std::this_thread::sleep_for(std::chrono::milliseconds((int)(1 * (1.0 / gm._fpsLimit - gm._acc))));
        }
    }

    GameManager& GameManager::get_instance()
    {
        // This is instantiated on first use and guaranteed to be the only one
        static GameManager instance;
        return instance;
    }

    void GameManager::push_state(State* newState)
    {
        // Make sure the game is not paused
        gm._running = true;

        // Add new state
        newState->on_init();
        gm._states.push_back(newState);
    }

    void GameManager::pop_state()
    {
        // Remove latest added state and stop if there are no states
        gm._states.pop_back();
        if(gm._states.size() == 0)
            gm._running = false;
    }

    void GameManager::limit_FPS(int32_t newLimit)
    {
        gm._fpsLimit = newLimit;
    }

    bool GameManager::is_running()
    {
        return gm._running;
    }

    #undef gm
};
