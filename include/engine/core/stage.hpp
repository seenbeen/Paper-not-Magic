#pragma once
#include <map>

#include <engine/core/engine.hpp>
#include <engine/core/finite-state-machine.hpp>
#include <engine/core/game-object.hpp>

// temp include
#include <iostream>

namespace MNPCore {
    template <typename StateEnum>
    class Stage : public FSMState<Engine, StateEnum> {
        std::map<std::string,GameObject*> m_objects;
        std::map<std::string,GameObject*> m_stagedObjects; // stuff to be inserted/spawned for next frame

    protected:
        virtual void onEnter(Engine &engineContext) = 0;
        virtual void onUpdate(Engine &engineContext, const float &deltaTime) = 0;
        virtual void onPostUpdate(Engine &engineContext) = 0;
        virtual void onExit(Engine &EngineContext) = 0;

    public:
        Stage(StateEnum e) : FSMState<Engine,StateEnum>(e) {}

        ~Stage() {}

        void enter(Engine &engineContext) {
            onEnter(engineContext); // stage loading done here.

            // add in all new stuff
            std::map<std::string,GameObject*>::iterator it;
            for (it = m_stagedObjects.begin(); it != m_stagedObjects.end(); ++it) {
                m_objects[it->first] = it->second;
                it->second->onEnter(engineContext);
            }
            m_stagedObjects.clear();
        }

        void update(Engine &engineContext) {
            const float deltaTime = engineContext.getDeltaTime();
            onUpdate(engineContext,deltaTime);

            std::map<std::string,GameObject*>::iterator it;

            // update all current stuff
            for (it = m_objects.begin(); it != m_objects.end(); ++it) {
                it->second->onUpdate(engineContext,deltaTime);
            }

            // give objects a chance to settle their states
            for (it = m_objects.begin(); it != m_objects.end(); ++it) {
                it->second->onPostUpdate(engineContext);
            }

            // clear out all dead stuff
            for (it = m_objects.begin(); it != m_objects.end(); ++it) {
                if (it->second->isDead()) {
                    it->second->onExit(engineContext);
                    delete it->second;
                    m_objects.erase(it++);
                }
            }

            // add in all new stuff
            for (it = m_stagedObjects.begin(); it != m_stagedObjects.end(); ++it) {
                m_objects[it->first] = it->second;
                it->second->onEnter(engineContext);
            }
            m_stagedObjects.clear();

            onPostUpdate(engineContext);
        }

        void exit(Engine &engineContext) {
            if (m_stagedObjects.size()) {
                // this should never occur!
                std::cout << "ermergerd staged objects were leaked during exit!" << std::endl;
            }

            std::map<std::string,GameObject*>::iterator it;
            for (it = m_objects.begin(); it != m_objects.end(); ++it) {
                it->second->onExit(engineContext);
                delete it->second;
            }
            m_objects.clear();

            onExit(engineContext); // stage unloading done here
        }

        template <class GameObjectType>
        bool addObject(const std::string &objectName) {
            if (m_stagedObjects.find(objectName) != m_stagedObjects.end()) {
                // warn!
                return false;
            } else if (m_objects.find(objectName) != m_objects.end()) {
                // warn again!
                return false;
            }
            m_stagedObjects[objectName] = new GameObjectType();
            return true;
        }
    };
}
