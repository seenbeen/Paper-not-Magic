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
        for (it = m_components.begin(); it != m_components.end(); ++it) {
            it->second->onLoad(engineContext, *this);
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
            it->second->onEnter(engineContext, *this);
        }
    }

    void GameObject::onUpdate(Engine &engineContext, const float &deltaTime) {
        std::map<std::string,GameObjectComponent*>::iterator it;
        for (it = m_components.begin(); it != m_components.end(); ++it) {
            it->second->onUpdate(engineContext, *this, deltaTime);
        }
    }

    void GameObject::onPostUpdate(Engine &engineContext) {
        std::map<std::string,GameObjectComponent*>::iterator it;
        for (it = m_components.begin(); it != m_components.end(); ++it) {
            it->second->onPostUpdate(engineContext, *this);
        }

        // kill all dedded stuff
        // Note: guarantee the component name exists in components
        std::set<std::string>::iterator deadIt;
        for (deadIt = m_deadComponents.begin(); deadIt != m_deadComponents.end(); ++deadIt) {
            it = m_components.find(*deadIt);
            it->second->onExit(engineContext, *this);
            delete it->second;
            m_components.erase(it);
        }
        m_deadComponents.clear();

        // push in all new stuff
        for (it = m_stagedComponents.begin(); it != m_stagedComponents.end(); ++it) {
            m_components[it->first] = it->second;
            it->second->onEnter(engineContext, *this);
        }
        m_stagedComponents.clear();
    }

    void GameObject::onExit(Engine &engineContext) {
        std::map<std::string,GameObjectComponent*>::iterator it;
        for (it = m_components.begin(); it != m_components.end(); ++it) {
            it->second->onExit(engineContext, *this);
        }
    }

    void GameObject::onUnload(Engine &engineContext) {
        std::map<std::string,GameObjectComponent*>::iterator it;
        for (it = m_components.begin(); it != m_components.end(); ++it) {
            it->second->onUnload(engineContext, *this);
        }
    }

    GameObject::GameObject() {
        m_dead = false;
    }

    GameObject::~GameObject() {}

    void GameObject::kill() {
        if (m_dead) {
            // should probably warn here
            return;
        }
        m_dead = false;
    }
}
