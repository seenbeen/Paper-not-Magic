#include <map>
#include <set>
#include <string>

#include <engine/core/game-object-component.hpp>
#include <engine/core/game-object.hpp>

namespace MNPCore {
    bool GameObject::isDead() {
        return m_dead;
    }

    void GameObject::onLoad(Engine &engineContext) {
        std::map<std::string,GameObjectComponent*>::iterator it;
        for (it = m_stagedComponents.begin(); it != m_stagedComponents.end(); ++it) {
            it->second->onLoad(engineContext);
        }
    }

    void GameObject::onEnter(Engine &engineContext) {
        std::map<std::string,GameObjectComponent*>::iterator it;

        // presumably load in components from constructor
        for (it = m_stagedComponents.begin(); it != m_stagedComponents.end(); ++it) {
            m_components[it->first] = it->second;
        }
        m_stagedComponents.clear();

        // everyone gets to go in :)
        for (it = m_components.begin(); it != m_components.end(); ++it) {
            it->second->onEnter(engineContext);
        }
    }

    void GameObject::onUpdate(Engine &engineContext, const float &deltaTime) {
        std::map<std::string,GameObjectComponent*>::iterator it;
        for (it = m_components.begin(); it != m_components.end(); ++it) {
            it->second->onUpdate(engineContext, deltaTime);
        }
    }

    void GameObject::onPostUpdate(Engine &engineContext) {
        std::map<std::string,GameObjectComponent*>::iterator it;
        for (it = m_components.begin(); it != m_components.end(); ++it) {
            it->second->onPostUpdate(engineContext);
        }

        // push in all new stuff
        for (it = m_stagedComponents.begin(); it != m_stagedComponents.end(); ++it) {
            m_components[it->first] = it->second;
            it->second->onEnter(engineContext);
        }
        m_stagedComponents.clear();
    }

    void GameObject::onExit(Engine &engineContext) {
        std::map<std::string,GameObjectComponent*>::iterator it;
        for (it = m_components.begin(); it != m_components.end(); ++it) {
            it->second->onExit(engineContext);
        }
    }

    void GameObject::onUnload(Engine &engineContext) {
        std::map<std::string,GameObjectComponent*>::iterator it;
        for (it = m_stagedComponents.begin(); it != m_stagedComponents.end(); ++it) {
            it->second->onUnload(engineContext);
        }
    }

    GameObject::GameObject() {
        m_dead = false;
    }

    GameObject::~GameObject() {
        std::map<std::string,GameObjectComponent*>::iterator it;
        for (it = m_stagedComponents.begin(); it != m_stagedComponents.end(); ++it) {
            delete it->second;
        }
    }

    void GameObject::kill() {
        if (m_dead) {
            // should probably warn here
            return;
        }
        m_dead = false;
    }
}
