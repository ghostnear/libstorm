#ifndef LIBSTORM_GAME_MANAGER_HPP
#define LIBSTORM_GAME_MANAGER_HPP

#include "deps.hpp"
#include "system/node.hpp"
#include <vector>
#include <thread>
#include <chrono>

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

        void assignGameManager(GameManager* gm);

    protected:
        Node* root = new Node();
        GameManager* _gm;
    };

    class GameManager
    {
    public:
        // Methods
        static void draw();
        static void delay();
        static void update();
        static GameManager& getInstance();
        static double getDeltaTime();
        static void pushState(State* newState);
        static void popState();
        static void limitFPS(int32_t newLimit);
        static bool isRunning();

    private:
        GameManager();

        std::vector<State*> _states;
        bool _running = false;
        int32_t _fpsLimit = -1;
        double  _acc = 0;
        double _dt = 0;
        uint64_t _now = 0, _last = 0;
    };
};

#endif
