#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include <mnp/framework/ui/shapes.hpp>
/*
Create an instance of InputHandler

Put listeners with addReceiver(should be your handler NOT game objects)(Will send inputs IN ORDER(To a root node))

Add your gameobjects(INHERIT inputcontext) to the appropriate receiver(In the appropriate order)

Implement the virtual functions required.



*/
namespace MNPInput {
    class InputContext;

    class InputHandler{

        std::list<InputContext*> m_receivers;
    public:

        bool addReceiver(InputContext *newReceiver);
        void sendEvent(sf::Event *event);

        void update(sf::Time deltaTime);
    };


    class InputContext {
    public:
        InputContext();
        virtual ~InputContext();
        std::list<InputContext*> m_children;

        virtual bool handleInput(sf::Event *event) = 0;
        virtual void update(sf::Time deltaTime) = 0;


        bool propogateToChildren(sf::Event *event);
        void propogateUpdate(sf::Time deltaTime);

        bool addContextChild(InputContext *newChild);

        virtual bool wantsFocus(sf::Event *event) = 0;
    };
}
