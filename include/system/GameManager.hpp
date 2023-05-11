#pragma once

#include "deps.hpp"
#include "system/all.hpp"
#include <vector>
#include <thread>
#include <chrono>

namespace Storm
{
    class State
    {
    public:
        virtual void on_init()
        {

        }

        virtual void draw()
        {
            Graphics::clear(0, 0, 0);

            // Draw scene
            root->execute_all("draw");

            Graphics::update();
        }

        virtual void update()
        {
            // Press escape to close window
        #ifndef VITA
            if(Input::isKeyReleased(SDLK_ESCAPE))
                Window::close();
        #endif

            // Update scene
            root->execute_all("update");
        }

        virtual ~State()
        {
            delete root;
        }

    protected:
        Node* root = new Node();
    };

    class GameManager
    {
    public:
        // Methods
        static void draw();
        static void update();
        static GameManager& get_instance();
        static double get_delta_time();
        static void push_state(State* newState);
        static void pop_state();
        static void pop_all_states();
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
