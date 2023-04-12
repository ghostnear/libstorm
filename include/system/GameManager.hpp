#ifndef LIBSTORM_GAME_MANAGER_HPP
#define LIBSTORM_GAME_MANAGER_HPP

#include "deps.hpp"
#include "system/Node.hpp"
#include <vector>
#include <thread>
#include <chrono>

namespace Storm
{
    class GameManager;

    class State
    {
    public:
        virtual void on_init() = 0;
        virtual void on_destroy() = 0;
        virtual void draw() = 0;
        virtual void update(double dt) = 0;

        void assign_game_manager(GameManager* gm);

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
        static GameManager& get_instance();
        static double get_delta_time();
        static void push_state(State* newState);
        static void pop_state();
        static void limit_FPS(int32_t newLimit);
        static bool is_running();

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
