#ifndef LIBSTORM_GAME_MANAGER_HPP
#define LIBSTORM_GAME_MANAGER_HPP

#include "deps.hpp"
#include "ecs.hpp"
#include "oop.hpp"
#include "systems.hpp"
#include <vector>

namespace Storm
{
    class GameManager;

    class State
    {
    public:
        virtual void onInit() = 0;
        virtual void onDestroy() = 0;
        virtual void draw() = 0;
        virtual void update(double dt) = 0;

        void assignGameManager(GameManager* gm) {_gm = gm;}

    protected:
        GameManager* _gm;
    };

    class ECSState : public State
    {
    public:
        // Assigns the default components
        ECSState()
        {
            assignDefaultComponents(&w);

            Signature sgn;
            sgn.set(w.getComponentType<Text>());
            sys.push_back(w.registerSystem<TextSystem>());
            sgn.reset();
        }

    protected:
        ECSWorld w;
        std::vector<std::shared_ptr<System>> sys;
    };

    class OOPState : public State
    {
    protected:
        OOPWorld w;
    };
    

    class GameManager
    {
    public:
        static GameManager& getInstance()
        {
            // This is instantiated on first use and guaranteed to be the only one
            static GameManager instance;
            return instance;
        }

        // Methods
        static void draw();
        static void update();
        static void pushState(State* newState);
        static void popState();
        static bool isRunning() {   return GameManager::getInstance()._running; }
        static double getFPS();

    private:
        GameManager();

        std::vector<State*> _states;
        bool _running = false;
        double _dt = 0;
        uint64_t _now = 0, _last = 0;
    };
};

#endif