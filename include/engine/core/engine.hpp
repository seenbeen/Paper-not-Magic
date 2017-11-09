#pragma once
#include <vector>

#include <engine/core/finite-state-machine.hpp>
#include <engine/render/renderer.hpp>

namespace MNPCore {
    class BaseEngineConfig;

    class Engine {
        bool m_isInitialized;
        bool m_isRunning;
        BaseFSM<Engine> *m_fsm;
        MNPRender::Renderer *m_renderer;
        sf::Clock m_clock;
        float m_deltaTime;

    public:
        Engine();
        void initialize(BaseEngineConfig *config);
        void run();
        void stop();
        void shutdown();

        // expose some getters to access engine modules
        float getDeltaTime();
        MNPRender::Renderer &getRenderer();
    };
}
