#include <engine/render/renderer.hpp>

#include <string>
#include <map>
#include <SFML/Graphics.hpp>
#include <engine/render/scene.hpp>

namespace MNPRender {
    /*
        For now, blatantly hard-coded window dimensions n stuff...
        Later on we'll come back to adjust this stuff and make it customizable
    */
    Renderer::Renderer()
        : m_window(sf::VideoMode(800, 600), "Seenbeen is(n't) boosted!",
                   sf::Style::Titlebar | sf::Style::Close) {}

    Renderer::~Renderer() {
        // scenes and compositing trees do not belong to the renderer per se
        // and should be deleted by the caller
        m_window.close();
    }

    bool Renderer::addScene(const std::string &sceneName, Scene &scene) {
        std::map<std::string,Scene*>::iterator it;
        it = m_scenes.find(sceneName);
        if (it != m_scenes.end()) {
            // should probably warn about what happened
            return false;
        }
        m_scenes[sceneName] = &scene;
        return true;
    }

    bool Renderer::removeScene(const std::string &sceneName) {
        std::map<std::string,Scene*>::iterator it;
        it = m_scenes.find(sceneName);
        if (it == m_scenes.end()) {
            // should probably warn about what happened
            return false;
        }
        m_scenes.erase(it);
        return true;
    }

    Scene *Renderer::getScene(const std::string &sceneName) {
        std::map<std::string,Scene*>::iterator it;
        it = m_scenes.find(sceneName);
        if (it == m_scenes.end()) {
            // should probably warn about what happened
            return NULL;
        }
        return it->second;
    }

    /*bool Renderer::addCompositingTree(const std::string &treeName, CompositingTree &tree) {};
    bool Renderer::removeCompositingTrees(const std::string &treeName) {};
    CompositingTree *Renderer::getCompositingTree(const std::string &treeName) {};*/

    void Renderer::update(const float &deltaTime) {
        m_window.clear();
        std::map<std::string,Scene*>::iterator it;
        for (it = m_scenes.begin(); it != m_scenes.end(); ++it) {
            it->second->update(deltaTime);
            it->second->render(m_window);
        }
        m_window.display();
    }
}

