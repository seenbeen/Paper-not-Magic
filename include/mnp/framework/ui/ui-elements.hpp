#pragma once
#include <list>

#include <SFML/Graphics.hpp>

#include <engine/input/input-context-component.hpp>
#include <engine/core/game-object.hpp>
#include <engine/core/game-object-component.hpp>

#include <mnp/framework/ui/ui-framework.hpp>

// UI Objects
/*
    Notes:
    - All UIObjects will have a UIManagementComponent, which takes care of synchronization logistics
      between components

    - Any UIObject must guarantee that a component called InputContextComponent,
      which is of base class UIContextComponent is added in the constructor

    - Any UIComponents added to a UIObject should be of base class UIComponent
*/

namespace MNPFrame {
    class UIRootObject : public UIObject {
    public:
        UIRootObject();
        UIContextComponent *getContextComponent();
    };

    class UIRootContextComponent : public UIContextComponent {
    public:
        bool killWindow;
        UIRootContextComponent();
        ~UIRootContextComponent();
        void handleEventImpl(const sf::Event &event, bool &willPropagate, bool &wantsFocus);
        void onPostUpdate(MNPCore::Engine &engineContext);
    };

    class UIRootComponent : public UIObjectComponent {
        UIRootContextComponent *m_context;
    public:
        void onLoad(MNPCore::Engine &engineContext);
        void onEnter(MNPCore::Engine &engineContext);
        void onUpdate(MNPCore::Engine &engineContext, const float &deltaTime);
        void onPostUpdate(MNPCore::Engine &engineContext);
        void onExit(MNPCore::Engine &engineContext);
        void onUnload(MNPCore::Engine &engineContext);
    };

    class UIButtonObject : public UIObject {
    public:
        UIButtonObject();
    };

    class UIButtonContext : public UIContextComponent {
        bool m_clicked;

    public:
        bool buttonClicked();
        void handleEventImpl(const sf::Event &event, bool &willPropagate, bool &wantsFocus);
        void onPostUpdate(MNPCore::Engine &engineContext);
    };

    class UIButtonTestComponent : public UIObjectComponent {
        UIManagementComponent *managementComp;
        UIButtonContext *buttonContext;

        sf::RectangleShape m_drawShape;

    public:
        UIButtonTestComponent();
        ~UIButtonTestComponent();
        void setColor(const sf::Color &color);
        void onLoad(MNPCore::Engine &engineContext);
        void onEnter(MNPCore::Engine &engineContext);
        void onUpdate(MNPCore::Engine &engineContext, const float &deltaTime);
        void onPostUpdate(MNPCore::Engine &engineContext);
        void onExit(MNPCore::Engine &engineContext);
        void onUnload(MNPCore::Engine &engineContext);
    };
}
