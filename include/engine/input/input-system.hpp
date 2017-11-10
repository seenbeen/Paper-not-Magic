#pragma once
#include <SFML/Graphics.hpp>
#include <list>

namespace MNPInput {
    class InputContext;

    class InputHandler{
        std::list<InputContext*> m_receivers;

    public:
        InputHandler();
        ~InputHandler();

        bool addReceiver(InputContext *newReceiver);
        void sendEvent(const sf::Event &event);

        void update(const float &deltaTime);
    };


    class InputContext {
        std::list<InputContext*> m_children;
    public:
        InputContext();
        virtual ~InputContext();

        bool addContextChild(InputContext *newChild);
        bool propogateToChildren(const sf::Event &event);
        void propogateUpdate(const float &deltaTime);

        virtual void update(const float &deltaTime) = 0;
        virtual bool handleInput(const sf::Event &event) = 0;
        virtual bool wantsFocus(const sf::Event &event) = 0;
    };
}
