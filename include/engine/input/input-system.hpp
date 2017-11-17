#pragma once
#include <list>

#include <SFML/Graphics.hpp>


namespace MNPInput {
    class InputContext {
        std::list<InputContext*> m_children;
    public:
        InputContext();
        virtual ~InputContext();

        bool addContextChild(InputContext *newChild);
        // will eventually need a remove here
        void propagateEvent(const sf::Event &event, bool &willPropagate, bool &wantsFocus);

        virtual void handleEvent(const sf::Event &event, bool &willPropagate, bool &wantsFocus) = 0;
    };

    class PassThroughContext : public InputContext {
    public:
        virtual void handleEvent(const sf::Event &event, bool &willPropagate, bool &wantsFocus);
    };

    class InputHandler{
        PassThroughContext m_contextRoot;

    public:
        InputHandler();
        ~InputHandler();

        bool addContext(InputContext *context);
        void sendEvent(const sf::Event &event);
    };
}
