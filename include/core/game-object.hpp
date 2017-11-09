#pragma once
#include <list>

#include <core/game-object-component.hpp>

namespace MNPCore {
    class Engine;
    class BaseGameObject {
    public:
        virtual ~BaseGameObject() {}
        virtual void onLoad(Engine &engineContext) = 0;
        virtual void onEnter(Engine &engineContext) = 0;
        virtual void onUpdate(Engine &engineContext, const float &deltaTime) = 0;
        virtual void onExit(Engine &engineContext) = 0;
        virtual void onUnload(Engine &engineContext) = 0;
        virtual bool isDead() = 0;
    };

    template <class GameObjContext>
    class GameObject : public BaseGameObject {
        std::list<GameObjectComponent<GameObjContext>*> m_components;
        GameObjContext &m_objContext;
        bool m_isDead;

    protected:
        void addComponent(GameObjectComponent<GameObjContext> *component) {
            m_components.push_back(component);
        }

    public:
        GameObject(GameObjContext &objContext)
            : m_objContext(objContext), m_isDead(false) {}

        bool isDead() {
            return m_isDead;
        }

        // needs to guarantee that all components have been loaded by the time entrance happens
        void onLoad(Engine &engineContext) {
            typename std::list<GameObjectComponent<GameObjContext>*>::iterator it;
            for (it = m_components.begin(); it != m_components.end(); ++it) {
                (*it)->onLoad(engineContext, m_objContext);
            }
        }

        void onEnter(Engine &engineContext) {
            typename std::list<GameObjectComponent<GameObjContext>*>::iterator it;
            for (it = m_components.begin(); it != m_components.end(); ++it) {
                (*it)->onEnter(engineContext, m_objContext);
            }
        }

        void onUpdate(Engine &engineContext, const float &deltaTime) {
            typename std::list<GameObjectComponent<GameObjContext>*>::iterator it;
            for (it = m_components.begin(); it != m_components.end(); ++it) {
                (*it)->onUpdate(engineContext, m_objContext, deltaTime);
            }
        }

        void onExit(Engine &engineContext) {
            typename std::list<GameObjectComponent<GameObjContext>*>::iterator it;
            for (it = m_components.begin(); it != m_components.end(); ++it) {
                (*it)->onExit(engineContext, m_objContext);
            }
        }

        // needs to guarantee that all components will be unloaded after exit happens
        // but before deletion
        void onUnload(Engine &engineContext) {
            typename std::list<GameObjectComponent<GameObjContext>*>::iterator it;
            for (it = m_components.begin(); it != m_components.end(); ++it) {
                (*it)->onUnload(engineContext, m_objContext);
            }
        }
    };
}
