#include "system/gamemanager.hpp"

namespace Storm
{
    void State::assignGameManager(GameManager* gm) 
    {
        _gm = gm;
    }

    ECSState::ECSState()
    {
        assignDefaultComponents(&w);

        Signature sgn;
        sgn.set(w.getComponentType<Text>());
        sys.push_back(w.registerSystem<TextSystem>());
        sgn.reset();
    }

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

        if(gm._fpsLimit < 1)
            for(auto i : gm._states)
                i -> update(gm._dt);
        else
        {
            gm._acc += gm._dt;
            while(gm._acc >= 1.0 / gm._fpsLimit)
            {
                gm._dt = 1.0 / gm._fpsLimit;
                for(auto i : gm._states)
                    i -> update(gm._dt);
                gm._acc -= 1.0 / gm._fpsLimit;
            }
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