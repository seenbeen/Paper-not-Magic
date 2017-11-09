#pragma once
#include <list>

#include <engine/core/engine.hpp>
#include <engine/core/finite-state-machine.hpp>
#include <engine/core/game-object.hpp>

namespace MNPCore {
    template <typename StateEnum>
    class Stage : public FSMState<Engine, StateEnum> {
        std::list<BaseGameObject*> m_objects;
        std::list<BaseGameObject*> m_stagedObjects; // stuff to be inserted/spawned for next frame

    protected:
        void addObject(BaseGameObject *object) {
            m_stagedObjects.push_back(object);
        }

    public:
        Stage(StateEnum e) : FSMState<Engine,StateEnum>(e) {}
        ~Stage() {
            if (m_stagedObjects.size() != 0) {
                //std::cout << "Warning, not all staged objects removed on stage deletion" << std::endl;
            }
            if (m_objects.size() != 0) {
                //std::cout << "Warning, not all objects unloaded on stage deletion" << std::endl;
            }
        }
        virtual void onEnter(Engine &engineContext) = 0;
        virtual void onUpdate(Engine &engineContext, const float &deltaTime) = 0;
        virtual void onExit(Engine &EngineContext) = 0;

        void enter(Engine &engineContext) {
            onEnter(engineContext);
        }

        void update(Engine &engineContext) {
            const float deltaTime = engineContext.getDeltaTime();
            onUpdate(engineContext,deltaTime);

            std::list<BaseGameObject*>::iterator it;
            BaseGameObject *curObject;

            // add in all new stuff
            for (it = m_stagedObjects.begin(); it != m_stagedObjects.end(); ++it) {
                curObject = *it;
                it = m_stagedObjects.erase(it);
                m_objects.push_back(curObject);
                curObject->onLoad(engineContext);
                curObject->onEnter(engineContext);
            }

            // update all current stuff
            for (it = m_objects.begin(); it != m_objects.end(); ++it) {
                curObject = *it;
                curObject->onUpdate(engineContext,deltaTime);
            }

            // clear out all dead stuff
            for (it = m_objects.begin(); it != m_objects.end(); ++it) {
                curObject = *it;
                if (curObject->isDead()) {
                    it = m_objects.erase(it);
                    curObject->onExit(engineContext);
                    curObject->onUnload(engineContext);
                    delete curObject;
                }
            }
        }

        void exit(Engine &engineContext) {
            onExit(engineContext);
            std::list<BaseGameObject*>::iterator it;
            BaseGameObject *curObject;

            for (it = m_stagedObjects.begin(); it != m_stagedObjects.end(); ++it) {
                curObject = *it;
                delete curObject;
            }

            m_stagedObjects.clear();

            for (it = m_objects.begin(); it != m_objects.end(); ++it) {
                curObject = *it;
                curObject->onExit(engineContext);
                curObject->onUnload(engineContext);
                delete curObject;
            }

            m_objects.clear();
        }
    };
}
