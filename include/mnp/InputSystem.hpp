#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include <mnp/shapes.hpp>
/*
Create an instance of InputHandler

Put listeners with addReceiver(should be your handler NOT game objects)(Will send inputs IN ORDER(To a root node))

Add your gameobjects(INHERIT inputcontext) to the appropriate receiver(In the appropriate order)

Implement the virtual functions required.



*/
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

class BaseUIContext : public InputContext {
    bool focusFlag;
public:
    // Used by ui to re-order rendering
    // Will reset focus state when called
    bool getFocus();
    bool wantsFocus(sf::Event *event);
    virtual bool wantsFocusImpl(sf::Event *event) = 0;

};


class UIClickableContext : public BaseUIContext {

public:
    UIClickableContext();
    ~UIClickableContext();

    Rectangle m_MyRect;
    bool clicked;

    void setRect(Rectangle r);

    bool handleInput(sf::Event *event);

    void update(sf::Time deltaTime);

    bool wantsFocusImpl(sf::Event *event);
};


class BlankContext : public BaseUIContext {
public:
    bool handleInput(sf::Event *event);
    void update(sf::Time deltaTime);

    bool wantsFocusImpl(sf::Event *event);
};

