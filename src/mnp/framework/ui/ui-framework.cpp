#include <SFML/Window/Event.hpp>

#include <mnp/framework/ui/ui-framework.hpp>

namespace MNPFrame {
// UIObject
    UIObject::UIObject() {
        m_uiManagementComponent = addComponent<UIManagementComponent>("UIManagementComponent");
        m_contextComponent = NULL;
    }

    UIObject::~UIObject() {}

    void UIObject::setDimensions(const sf::Vector2f &dims) {
        m_uiManagementComponent->setDimensions(dims);
    }

    bool UIObject::addUIObjectChild(UIObject *child) {
        m_uiManagementComponent->addComponentChild(child->m_uiManagementComponent);
        m_contextComponent->addContextChild(child->m_contextComponent);
        return true;
    }

    bool UIObject::removeUIObjectChild(UIObject *child) {
        return true;
    }

// UIObjectComponent

    UIObjectComponent::UIObjectComponent() {
        m_UIManagementComponent = NULL;
    }

    UIObjectComponent::~UIObjectComponent() {}

    UIManagementComponent *UIObjectComponent::getUIManagementComponent() {
        if (m_UIManagementComponent == NULL) {
            m_UIManagementComponent = gameObject().getComponent<UIManagementComponent>("UIManagementComponent");
        }
        return m_UIManagementComponent;
    }

// UIContextComponent
    UIContextComponent::UIContextComponent() {
        m_moveToFront = false;
    }

    UIContextComponent::~UIContextComponent() {}

    void UIContextComponent::setRect(const sf::FloatRect &r) {
        m_rect = r;
    }

    void UIContextComponent::handleEvent(const sf::Event &event, bool &willPropagate, bool &wantsFocus) {
        handleEventImpl(event, willPropagate, wantsFocus);
        if (wantsFocus) {
            m_moveToFront = true;
        }
    }

    bool UIContextComponent::isClicked(const sf::Vector2f &pt) {
        return m_rect.contains(pt);
    }

// UIManagementComponent
    UIContextComponent *UIManagementComponent::getContextComponent() {
        if (m_context == NULL) {
            m_context = gameObject().getComponent<UIContextComponent>("UIContextComponent");
        }
        return m_context;
    }

    void UIManagementComponent::moveComponent(const sf::Vector2f &delta) {
        gameObject().transform.position() += delta;
        m_oldPos += delta;
        m_rect.left = m_oldPos.x;
        m_rect.top = m_oldPos.y;
        getContextComponent()->setRect(m_rect);
        std::list<UIManagementComponent*>::iterator it;
        for (it = m_children.begin(); it != m_children.end(); ++it) {
            (*it)->moveComponent(delta);
        }
    }

    void UIManagementComponent::_reserializeDepth(int &depthCounter) {
        gameObject().transform.depth() = depthCounter++;
        std::list<UIManagementComponent*>::iterator it;
        for (it = m_children.begin(); it != m_children.end(); ++it) {
            (*it)->_reserializeDepth(depthCounter);
        }
    }

    bool UIManagementComponent::moveToFront() {
        if (m_context->m_moveToFront) {
            m_context->m_moveToFront = false;
            return true;
        }
        return false;
    }

    UIManagementComponent::UIManagementComponent() {
        m_context = NULL;
        m_firstChild = NULL;
    }
    UIManagementComponent::~UIManagementComponent() {}

    sf::FloatRect UIManagementComponent::getRect() {
        return m_rect;
    }

    void UIManagementComponent::reserializeDepth(int &depthCounter) {
        if (m_children.size()) {
            if (m_firstChild != *m_children.begin()) {
                m_firstChild = *m_children.begin();
                int depthCounter = gameObject().transform.depth();
                _reserializeDepth(depthCounter);
            }
        }
    }

    void UIManagementComponent::addComponentChild(UIManagementComponent *child) {
        m_children.push_back(child);
    }

    void UIManagementComponent::setDimensions(const sf::Vector2f &dims) {
        m_rect.width = dims.x;
        m_rect.height = dims.y;
        getContextComponent()->setRect(m_rect);
    }

    void UIManagementComponent::onLoad(MNPCore::Engine &engineContext) {}

    void UIManagementComponent::onEnter(MNPCore::Engine &engineContext) {}

    void UIManagementComponent::onUpdate(MNPCore::Engine &engineContext, const float &deltaTime) {}

    void UIManagementComponent::onPostUpdate(MNPCore::Engine &engineContext) {
        sf::Vector2f delta = gameObject().transform.position() - m_oldPos;
        std::list<UIManagementComponent*>::iterator it, tmp;
        if (delta.x || delta.y) {
            for (it = m_children.begin(); it != m_children.end(); ++it) {
                (*it)->moveComponent(delta);
            }
            m_oldPos += delta;
        }
        // basically move all the stuff that wants to be moved to the front
        it = m_children.begin();
        while (it != m_children.end()) {
            if ((*it)->moveToFront()) {
                tmp = it;
                ++tmp;
                m_children.push_front(*it);
                m_children.erase(it);
                it = tmp;
            } else {
                ++it;
            }
        }
        int depthCounter = gameObject().transform.depth();
        reserializeDepth(depthCounter);
    }

    void UIManagementComponent::onExit(MNPCore::Engine &engineContext) {}

    void UIManagementComponent::onUnload(MNPCore::Engine &engineContext) {}
}

