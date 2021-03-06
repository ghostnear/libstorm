#ifndef LIBSTORM_GAME_MANAGER_HPP
#define LIBSTORM_GAME_MANAGER_HPP

#include "deps.hpp"
#include "ecs/all.hpp"
#include "oop/all.hpp"
#include "system/all.hpp"
#include <vector>
#include <thread>
#include <chrono>

namespace Storm
{
    namespace Utils
    {
        template<typename T>
        inline std::string to_stringt(T arg)
        {
            std::ostringstream ss;
            ss << arg;
            return ss.str();
        }
    };

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
        GameManager* _gm;
    };

    class ECSState : public State
    {
    public:
        ECSState();

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
        // Methods
        static void draw();
        static void delay();
        static void update();
        static GameManager& getInstance();
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