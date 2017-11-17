#include <engine/render/renderer.hpp>

#include <string>
#include <map>
#include <SFML/Graphics.hpp>
#include <engine/render/scene.hpp>

namespace MNPRender {
    Renderer::DebugShape::DebugShape(sf::Shape *shape, const int &depth, const float &duration)
        : shape(shape), depth(depth), duration(duration) {}

    Renderer::DebugShape::~DebugShape() {
        delete shape;
    }

    bool Renderer::DebugShape::compareDebugShape(const DebugShape *A, const DebugShape *B) {
        return A->depth > B->depth;
    }

    void Renderer::renderDebugShapes(const float &deltaTime) {
        m_debugShapes.sort(DebugShape::compareDebugShape);
        std::list<DebugShape*>::iterator it;
        it = m_debugShapes.begin();
        while (it != m_debugShapes.end()) {
            m_window.draw(*(*it)->shape);
            (*it)->duration -= deltaTime;
            if ((*it)->duration <= 0.0f) {
                delete *it;
                it = m_debugShapes.erase(it);
            } else {
                ++it;
            }
        }
    }

    Renderer::Renderer(sf::RenderWindow &window) : m_window(window) {}

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

        renderDebugShapes(deltaTime);
        m_window.display();
    }

    void Renderer::debugCircleShape(const sf::CircleShape &shape, const int &depth, const float &duration) {
        sf::Shape *shape_copy = new sf::CircleShape(shape);
        m_debugShapes.push_back(new DebugShape(shape_copy,depth,duration));
    }

    void Renderer::debugRectangleShape(const sf::RectangleShape &shape, const int &depth, const float &duration) {
        sf::Shape *shape_copy = new sf::RectangleShape(shape);
        m_debugShapes.push_back(new DebugShape(shape_copy,depth,duration));
    }

    void Renderer::debugConvexShape(const sf::ConvexShape &shape, const int &depth, const float &duration) {
        sf::Shape *shape_copy = new sf::ConvexShape(shape);
        m_debugShapes.push_back(new DebugShape(shape_copy,depth,duration));
    }
}

