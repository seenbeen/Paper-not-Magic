#pragma once
#include <map>
#include <set>
#include <string>

#include <engine/core/game-object-component.hpp>

namespace MNPCore {
    class Engine;

    class GameObject {
        bool m_dead;
        std::map<std::string,GameObjectComponent*> m_stagedComponents;
        std::map<std::string,GameObjectComponent*> m_components;
        std::set<std::string> m_deadComponents;

    public:
        bool isDead();
        // needs to guarantee that all components have been loaded by the time entrance happens
        void onLoad(Engine &engineContext);
        void onEnter(Engine &engineContext);
        void onUpdate(Engine &engineContext, const float &deltaTime);
        void onPostUpdate(Engine &engineContext);
        void onExit(Engine &engineContext);
        // needs to guarantee that all components will be unloaded after exit happens
        // but before deletion
        void onUnload(Engine &engineContext);

        GameObject();
        ~GameObject();

        void kill();

        template <class ComponentClass>
        bool addComponent(const std::string &componentName) {
            if (m_dead) {
                // should probably warn here
                return false;
            } else if (m_stagedComponents.find(componentName) != m_stagedComponents.end()) {
                // we're staged already!
                return false;
            } else if (m_components.find(componentName) != m_components.end()) {
                // we already exist!
                return false;
            }
            m_stagedComponents[componentName] = new ComponentClass();
            return true;
        }

        bool removeComponent(const std::string &componentName) {
            if (m_dead) {
                // should probably warn here
                return false;
            } else if (m_components.find(componentName) == m_components.end()) {
                // we don't exist!
                return false;
            } else if (m_deadComponents.find(componentName) != m_deadComponents.end()) {
                // we dead already!
                return false;
            }
            m_deadComponents.insert(componentName);
            return true;
        }

        template <class ComponentClass>
        ComponentClass *getComponent(const std::string &componentName) {
            if (m_dead) {
                // should probably warn here
                return NULL;
            } else if (m_components.find(componentName) == m_components.end()) {
                // we don't exist!
                return NULL;
            }
            return m_components.find(componentName)->second;
        }
    };
}
