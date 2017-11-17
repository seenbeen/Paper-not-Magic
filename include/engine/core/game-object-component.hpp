#pragma once

namespace MNPCore {
    class Engine;
    class GameObject;

    class GameObjectComponent {
    friend class GameObject;
        GameObject *m_gameObject;

    public:
        GameObjectComponent(){}
        virtual ~GameObjectComponent(){}

        GameObject &gameObject() { return *m_gameObject; }

        virtual void onLoad(Engine &engineContext) = 0;
        virtual void onEnter(Engine &engineContext) = 0;
        virtual void onUpdate(Engine &engineContext, const float &deltaTime) = 0;
        virtual void onPostUpdate(Engine &engineContext) = 0;
        virtual void onExit(Engine &engineContext) = 0;
        virtual void onUnload(Engine &engineContext) = 0;
    };
}
