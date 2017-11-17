#pragma once
#include <map>
#include <set>
#include <string>

#include <engine/core/math.hpp>
#include <engine/core/game-object-component.hpp>

namespace MNPCore {
    class Engine;

    class GameObject {
        bool m_dead;
        std::map<std::string,GameObjectComponent*> m_stagedComponents;
        std::map<std::string,GameObjectComponent*> m_components;

    public:
        MNPCore::Transform transform;

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
        ComponentClass *addComponent(const std::string &componentName) {
            if (m_dead) {
                // should probably warn here
                return NULL;
            } else if (m_stagedComponents.find(componentName) != m_stagedComponents.end()) {
                // we're staged already!
                return NULL;
            } else if (m_components.find(componentName) != m_components.end()) {
                // we already exist!
                return NULL;
            }
            ComponentClass *component = new ComponentClass();
            component->m_gameObject = this;
            m_stagedComponents[componentName] = component;
            return component;
        }

        template <class ComponentClass>
        ComponentClass *getComponent(const std::string &componentName) {
            if (m_dead) {
                // should probably warn here
                return NULL;
            } else if (m_components.find(componentName) != m_components.end()) {
                return dynamic_cast<ComponentClass*>(m_components.find(componentName)->second);
            } else if (m_stagedComponents.find(componentName) != m_stagedComponents.end()) {
                return dynamic_cast<ComponentClass*>(m_stagedComponents.find(componentName)->second);
            }
            // we don't exist!
            return NULL;
        }
    };
}
