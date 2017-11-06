#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <mnp/shapes.hpp>
#include <list>
#include <mnp/InputSystem.hpp>




class UIComponent {

protected:
    Rectangle m_rect;
    std::list<UIComponent*> m_children;


public:

    BaseUIContext *m_context;

    UIComponent(int x,int y,int l,int h,BaseUIContext *context);

    virtual ~UIComponent();

    bool addComponent(UIComponent *newChild);
    bool removeComponent (UIComponent *removeChild);

    void bindContext(BaseUIContext* toBind);

    void render(sf::RenderWindow &window);

    void update(sf::Time deltaTime);

    virtual void receiveRender(sf::RenderWindow &window) = 0;
    virtual void receiveUpdate(sf::Time deltaTime) = 0;

};

class UIBox : public UIComponent{
protected:
    sf::RectangleShape m_drawShape;
    BaseUIContext *m_context;
public:
    UIBox(int x,int y,int l,int w,BaseUIContext* context);
    ~UIBox();

    void receiveRender(sf::RenderWindow &window);
    void changeColor(sf::Color newColor);
    //bool propagate(sf::Event &event);
};

class UIButton : public UIBox {

    UIClickableContext* m_context;
public:


    UIButton(int x,int y,int l,int h,UIClickableContext* context);
    ~UIButton();

    void onClick();


    bool receiveEvent(sf::Event *event);
    //void receiveRender(sf::RenderWindow &window, Point &offSet);
    void receiveUpdate(sf::Time deltaTime);


};

class UITextInputBox : public UIComponent {
    std::string inputText;
    bool focus;
    UIClickableContext* m_context;
public:
    UITextInputBox(int x,int y,int l,int h,UIClickableContext* context);
    ~UITextInputBox();
    bool receiveEvent(sf::Event *event);
    void receiveRender(sf::RenderWindow &window);
    void receiveUpdate(sf::Time deltaTime);
};

class UIRoot : public UIComponent{
    BlankContext* m_context;

public:
    UIRoot(int x,int y,int l,int w,BlankContext* context);
    ~UIRoot();

    void receiveRender(sf::RenderWindow &window);
    void receiveUpdate(sf::Time deltaTime);
};

class UIHandler {
    UIComponent *m_root;
    InputContext *m_rootcontext;
    //game;
public:
    UIHandler(InputHandler* inputParent);
    ~UIHandler();

    bool bindRootUI(UIComponent *rootUI);

    void update(sf::Time deltaTime);
    void render(sf::RenderWindow &window);


};
