#pragma once
#include <list>

#include <SFML/Graphics.hpp>

#include <engine/input/input-system.hpp>
#include <engine/core/game-object.hpp>

#include <mnp/framework/ui/ui-context.hpp>

class UIComponent {
protected:
    sf::FloatRect m_rect;
    std::list<UIComponent*> m_children;

public:
    BaseUIContext *m_context;

    UIComponent(int x,int y,int l,int h,BaseUIContext *context);

    virtual ~UIComponent();

    bool addComponent(UIComponent *newChild);
    bool removeComponent (UIComponent *removeChild);

    void bindContext(BaseUIContext* toBind);

    void render(sf::RenderWindow &window);

    void update(const float &deltaTime);

    virtual void receiveRender(sf::RenderWindow &window) = 0;
    virtual void receiveUpdate(const float &deltaTime) = 0;

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
};

class UIButton : public UIBox {
    UIClickableContext* m_context;

public:
    UIButton(int x,int y,int l,int h,UIClickableContext* context);
    ~UIButton();

    void onClick();

    bool receiveEvent(const sf::Event &event);
    void receiveUpdate(const float &deltaTime);
};

class UITextInputBox : public UIComponent {
    std::string inputText;
    bool focus;
    UIClickableContext* m_context;

public:
    UITextInputBox(int x,int y,int l,int h,UIClickableContext* context);
    ~UITextInputBox();
    bool receiveEvent(const sf::Event &event);
    void receiveRender(sf::RenderWindow &window);
    void receiveUpdate(const float &deltaTime);
};

class UIRoot : public UIComponent{
    BlankContext* m_context;

public:
    UIRoot(int x,int y,int l,int w,BlankContext* context);
    ~UIRoot();

    void receiveRender(sf::RenderWindow &window);
    void receiveUpdate(const float &deltaTime);
};

class UIHandler {
    UIComponent *m_root;
    MNPInput::InputContext *m_rootcontext;

public:
    UIHandler(MNPInput::InputHandler* inputParent);
    ~UIHandler();

    bool bindRootUI(UIComponent *rootUI);

    void update(const float &deltaTime);
    void render(sf::RenderWindow &window);
};
