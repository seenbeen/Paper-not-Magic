#include <core/engine.hpp>
#include <core/engine-config.hpp>

namespace MNPCore {
    Engine::Engine()
        : m_isInitialized(false), m_isRunning(false) {}

    void Engine::initialize(BaseEngineConfig *config) {
        m_fsm = config->makeFSM();
        //m_renderer = new MNPRender::Renderer();
        m_isInitialized = true;
    }

    void Engine::run() {
        if (!m_isInitialized) {
            // should probably log something right here
            return;
        }

        m_isRunning = true;
        m_clock.restart(); // initial restart to reset ticks
        while (m_isRunning) {
            m_deltaTime = m_clock.restart().asSeconds();
            // m_input->update(m_deltaTime);
            m_fsm->update(*this);
            //m_renderer->update(m_deltaTime);
        }
    }

    void Engine::stop() {
        m_isRunning = false;
    }

    void Engine::shutdown() {
        if (m_isRunning) {
            return; // can't just kms while running
        }
        m_fsm->destroy(*this);

        // shutdown each subsystem instance
        //delete m_renderer;
        //m_renderer = NULL;

        m_isInitialized = false;
    }

    float Engine::getDeltaTime() {
        return m_deltaTime;
    }
}
