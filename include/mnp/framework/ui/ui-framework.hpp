#pragma once
#include <SFML/Window/Event.hpp>

#include <engine/core/engine.hpp>
#include <engine/core/game-object.hpp>
#include <engine/core/game-object-component.hpp>
#include <engine/input/input-context-component.hpp>

namespace MNPFrame {
    class UIManagementComponent;
    class UIContextComponent;

    class UIObject : public MNPCore::GameObject {
    protected:
        UIManagementComponent *m_uiManagementComponent;
        UIContextComponent *m_contextComponent;

    public:
        UIObject();
        ~UIObject();

        void setDimensions(const sf::Vector2f &dims);
        bool addUIObjectChild(UIObject *child);
        bool removeUIObjectChild(UIObject *child);
    };

    class UIContextComponent : public MNPInput::InputContextComponent {
    friend class UIManagementComponent;
        sf::FloatRect m_rect;
        bool m_moveToFront;

    public:
        UIContextComponent();
        ~UIContextComponent();

        void setRect(const sf::FloatRect &r);
        void handleEvent(const sf::Event &event, bool &willPropagate, bool &wantsFocus);
        bool isClicked(const sf::Vector2f &pt);

        virtual void handleEventImpl(const sf::Event &event, bool &willPropagate, bool &wantsFocus) = 0;
    };

    class UIManagementComponent : public MNPCore::GameObjectComponent {
        std::list<UIManagementComponent*> m_children;
        UIManagementComponent *m_firstChild;

        UIContextComponent *m_context;
        sf::Vector2f m_oldPos;
        sf::FloatRect m_rect;

        UIContextComponent *getContextComponent();

        void moveComponent(const sf::Vector2f &delta);

        void _reserializeDepth(int &depthCounter);

        bool moveToFront();

    public:
        UIManagementComponent();
        ~UIManagementComponent();

        sf::FloatRect getRect();
        void reserializeDepth(int &depthCounter);
        void addComponentChild(UIManagementComponent *child);
        void setDimensions(const sf::Vector2f &dims);

        void onLoad(MNPCore::Engine &engineContext);
        void onEnter(MNPCore::Engine &engineContext);
        void onUpdate(MNPCore::Engine &engineContext, const float &deltaTime);
        void onPostUpdate(MNPCore::Engine &engineContext);
        void onExit(MNPCore::Engine &engineContext);
        void onUnload(MNPCore::Engine &engineContext);
    };

    class UIObjectComponent : public MNPCore::GameObjectComponent {
        UIManagementComponent *m_UIManagementComponent;

    public:
        UIObjectComponent();
        ~UIObjectComponent();

        UIManagementComponent *getUIManagementComponent();

        template <class T>
        T *getUIContextComponent() {
            return gameObject().getComponent<T>("UIContextComponent");
        }
    };
}
