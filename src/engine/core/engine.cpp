#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

#include <engine/core/engine-config.hpp>
#include <engine/core/finite-state-machine.hpp>
#include <engine/render/renderer.hpp>
#include <engine/input/input-system.hpp>

#include <engine/core/engine.hpp>

namespace MNPCore {
    Engine::Engine()
        : m_isInitialized(false), m_isRunning(false) {
        m_inputHandler = NULL;
        m_renderer = NULL;
        m_deltaTime = 0.0f;
    }

    void Engine::initialize(BaseEngineConfig *config) {
        /*
            For now, blatantly hard-coded window dimensions n stuff...
            Later on we'll come back to adjust this stuff and make it customizable
        */
        m_window = new sf::RenderWindow(sf::VideoMode(800, 600), "Seenbeen is(n't) boosted!",
                                        sf::Style::Titlebar | sf::Style::Close);
        m_inputHandler = new MNPInput::InputHandler();
        m_renderer = new MNPRender::Renderer(*m_window);
        m_fsm = config->makeFSM();
        m_isInitialized = true;
    }

    void Engine::run() {
        if (!m_isInitialized) {
            // should probably log something right here
            return;
        }
        m_isRunning = true;
        m_clock.restart(); // initial restart to reset ticks
        sf::Event event;
        while (m_isRunning) {
            m_deltaTime = m_clock.restart().asSeconds();
            m_inputHandler->update(m_deltaTime);
            while (m_window->pollEvent(event)) {
                m_inputHandler->sendEvent(event);
            }
            m_fsm->update(*this);
            m_renderer->update(m_deltaTime);
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
        delete m_renderer;
        m_renderer = NULL;
        delete m_inputHandler;
        m_inputHandler = NULL;

        m_isInitialized = false;
    }

    float Engine::getDeltaTime() {
        return m_deltaTime;
    }

    MNPRender::Renderer &Engine::getRenderer() {
        return *m_renderer;
    }

    MNPInput::InputHandler &Engine::getInputHandler() {
        return *m_inputHandler;
    }

    // TODO: warn if loading twice or unloading non-existent occurs
    template <class GameObjectType>
    bool Engine::loadObject() {
        GameObjectType obj;
        obj.onLoad(*this);
        return true;
    }

    template <class GameObjectType>
    bool Engine::unloadObject() {
        GameObjectType obj;
        obj.onUnload(*this);
        return true;
    }
}
