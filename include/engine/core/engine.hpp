#pragma once
#include <vector>

#include <engine/core/finite-state-machine.hpp>
#include <engine/render/renderer.hpp>
#include <engine/input/input-system.hpp>

namespace MNPCore {
    class BaseEngineConfig;

    class Engine {
        BaseFSM<Engine> *m_fsm;
        sf::Clock m_clock;
        bool m_isInitialized;
        bool m_isRunning;
        float m_deltaTime;

        sf::RenderWindow *m_window;

        MNPRender::Renderer *m_renderer;
        MNPInput::InputHandler *m_inputHandler;

    public:
        Engine();
        void initialize(BaseEngineConfig *config);
        void run();
        void stop();
        void shutdown();

        // expose some getters to access engine modules
        float getDeltaTime();
        MNPRender::Renderer &getRenderer();
        MNPInput::InputHandler &getInputHandler();

        template <class GameObjectType>
        bool loadObject();

        template <class GameObjectType>
        bool unloadObject();
    };
}
