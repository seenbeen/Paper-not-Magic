#include <core/engine.hpp>

namespace MNPCore {
    Engine::Engine()
        : m_isInitialized(false), m_isRunning(false) {}

    void Engine::initialize(BaseEngineConfig *config) {
        m_fsm = config->makeFSM();
        m_isInitialized = true;
    }

    void Engine::run() {
        if (!m_isInitialized) {
            // should probably log something right here
            return;
        }

        m_isRunning = true;
        while (m_isRunning) {
            m_fsm->update(*this);
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
    }
}
