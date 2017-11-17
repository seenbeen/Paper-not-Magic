#include <list>

#include <SFML/Graphics.hpp>

#include <engine/core/engine.hpp>
#include <engine/core/game-object.hpp>
#include <engine/core/game-object-component.hpp>

#include <mnp/framework/ui/ui-framework.hpp>
#include <mnp/framework/ui/ui-elements.hpp>

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
// UIRootObject
    UIRootObject::UIRootObject() {
        m_contextComponent = addComponent<UIRootContextComponent>("UIContextComponent");
        addComponent<UIRootComponent>("UIRootComponent");
    }

    UIContextComponent *UIRootObject::getContextComponent() {
        return m_contextComponent;
    }

// UIRootContextComponent
    UIRootContextComponent::UIRootContextComponent() {
        killWindow = false;
    }

    UIRootContextComponent::~UIRootContextComponent() {}

    void UIRootContextComponent::handleEventImpl(const sf::Event &event, bool &willPropagate, bool &wantsFocus) {
        if (event.type == sf::Event::Closed) {
            killWindow = true;
            willPropagate = false;
        }
    }

    void UIRootContextComponent::onPostUpdate(MNPCore::Engine &engineContext) {}

// UIRootComponent
    void UIRootComponent::onLoad(MNPCore::Engine &engineContext) {};

    void UIRootComponent::onEnter(MNPCore::Engine &engineContext) {
        m_context = gameObject().getComponent<UIRootContextComponent>("UIContextComponent");
    };

    void UIRootComponent::onUpdate(MNPCore::Engine &engineContext, const float &deltaTime) {};

    void UIRootComponent::onPostUpdate(MNPCore::Engine &engineContext) {
        if (m_context->killWindow) {
            engineContext.stop();
        }
    };

    void UIRootComponent::onExit(MNPCore::Engine &engineContext) {};

    void UIRootComponent::onUnload(MNPCore::Engine &engineContext) {};

// UIButtonObject
    UIButtonObject::UIButtonObject() {
        m_contextComponent = addComponent<UIButtonContext>("UIContextComponent");
    }

// UIButtonContext
    bool UIButtonContext::buttonClicked() {
        return m_clicked;
    }

    void UIButtonContext::handleEventImpl(const sf::Event &event, bool &willPropagate, bool &wantsFocus) {
        willPropagate = false;
        if (event.type == sf::Event::MouseButtonPressed){
            if (event.mouseButton.button == sf::Mouse::Left){
                if (isClicked(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))){
                    m_clicked = true;
                    willPropagate = true;
                    wantsFocus = true;
                }
            }
        }
    }

    void UIButtonContext::onPostUpdate(MNPCore::Engine &engineContext) {
        if (m_clicked) {
            m_clicked = false;
        }
    }

// UIButtonTestComponent
    UIButtonTestComponent::UIButtonTestComponent() {}

    UIButtonTestComponent::~UIButtonTestComponent() {}

    void UIButtonTestComponent::setColor(const sf::Color &color) {
        m_drawShape.setFillColor(color);
    }

    void UIButtonTestComponent::onLoad(MNPCore::Engine &engineContext) {}

    void UIButtonTestComponent::onEnter(MNPCore::Engine &engineContext) {
        managementComp = getUIManagementComponent();
        buttonContext = getUIContextComponent<UIButtonContext>();
    }

    void UIButtonTestComponent::onUpdate(MNPCore::Engine &engineContext, const float &deltaTime) {
        sf::FloatRect rect = managementComp->getRect();
        m_drawShape.setSize(sf::Vector2f(rect.width,rect.height));
        m_drawShape.setPosition(sf::Vector2f(rect.left,rect.top));

        if (buttonContext->buttonClicked()) {
            m_drawShape.setFillColor(sf::Color(std::rand()%255,std::rand()%255,std::rand()%255));
        }

        // layer depth only supported between debug shapes (think of it like another layer)
        engineContext.getRenderer().debugRectangleShape(m_drawShape,gameObject().transform.depth());
    }

    void UIButtonTestComponent::onPostUpdate(MNPCore::Engine &engineContext) {}

    void UIButtonTestComponent::onExit(MNPCore::Engine &engineContext) {}

    void UIButtonTestComponent::onUnload(MNPCore::Engine &engineContext) {}
}
