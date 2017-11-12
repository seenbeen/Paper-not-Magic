#include <iostream>
#include <algorithm>
#include <vector>

#include <SFML/Graphics.hpp>
#include <engine/core/engine.hpp>
#include <engine/core/game-object-component.hpp>

#include <mnp/framework/ui/ui-elements.hpp>

//UI Components

UIComponent::UIComponent(int x,int y,int l,int h, BaseUIContext* context) : m_rect(x,y,l,h),m_context(context){}

UIComponent::~UIComponent(){
    for (std::list<UIComponent*>::iterator it = m_children.begin(); it != m_children.end(); it++) {
        delete (*it);
    }
}

bool UIComponent::addComponent(UIComponent *newChild) {
    m_children.push_back(newChild);
    m_context->addContextChild(newChild->m_context);

    return true;
}

bool UIComponent::removeComponent(UIComponent *removeChild) {
    for (std::list<UIComponent*>::iterator it = m_children.begin(); it != m_children.end(); it++) {
       if ((*it)==removeChild) {
            return false;
        }
    }
    return false;
}

void UIComponent::update(const float &deltaTime){
    receiveUpdate(deltaTime);
    std::list<UIComponent*>::iterator moveForward;
    bool moveToForward = false;

    for (std::list<UIComponent*>::iterator it = m_children.begin(); it != m_children.end(); it++) {
        if ((*it)->m_context->getFocus()){
            moveToForward = true;
            moveForward = it;
        }
        (*it)->update(deltaTime);
    }

    if (moveToForward){
        UIComponent* reinsert = *moveForward;
        m_children.erase(moveForward);
        m_children.push_back(reinsert);
    }
}

void UIComponent::render(MNPCore::Engine &engineContext){
    receiveRender(engineContext);
    for (std::list<UIComponent*>::iterator it = m_children.begin(); it != m_children.end(); it++) {
        (*it)->render(engineContext);
    }
}

UIBox::UIBox(int x,int y,int l,int h,BaseUIContext* context) : UIComponent(x,y,l,h,context),m_context(context) {
    m_drawShape = sf::RectangleShape(sf::Vector2f(m_rect.width, m_rect.height));
    m_drawShape.setFillColor(sf::Color(150, 50, 250));
}

UIBox::~UIBox() {
    delete m_context;
}

void UIBox::receiveRender(MNPCore::Engine &engineContext){
    m_drawShape.setPosition(m_rect.left,m_rect.top);
    engineContext.getRenderer().debugRectangleShape(m_drawShape);
}

void UIBox::changeColor(sf::Color newColor){
    m_drawShape.setFillColor(newColor);
}

UIButton::UIButton(int x,int y,int l,int h,UIClickableContext* context) : UIBox(x,y,l,h,context),m_context(context) {
    m_context->setRect(m_rect);
};

UIButton::~UIButton(){}

void UIButton::receiveUpdate(const float &deltaTime){
    if (m_context->clicked == true){
        changeColor(sf::Color(std::rand()%255,std::rand()%255,std::rand()%255));
    }
}

UIRoot::UIRoot(int x,int y,int l,int h,BlankContext* context) : UIComponent(x,y,l,h,context),m_context(context) {}

UIRoot::~UIRoot(){
    delete m_context;
}

void UIRoot::receiveRender(MNPCore::Engine &engineContext){}
void UIRoot::receiveUpdate(const float &deltaTime){}

UIHandler::UIHandler(){
    m_rootcontext = new BlankContext();
}

UIHandler::~UIHandler(){
    if (m_root != NULL){
        delete m_root;
    }
}

void UIHandler::onLoad(MNPCore::Engine &engineContext, MNPCore::GameObject &objContext) {

}

void UIHandler::onEnter(MNPCore::Engine &engineContext, MNPCore::GameObject &objContext) {
    engineContext.getInputHandler().addReceiver(m_rootcontext);
    m_root = new UIRoot(0,0,1280,720,new BlankContext());
    m_rootcontext->addContextChild(m_root->m_context);

    //UIClickableContext* button1context = new UIClickableContext();
    UIButton *myButton = new UIButton(50,50,100,100,new UIClickableContext());
    m_root->addComponent(myButton);

    UIButton *myButton2 = new UIButton(70,70,100,100,new UIClickableContext());
    m_root->addComponent(myButton2);

    myButton2->changeColor(sf::Color(255,255,255));
}

void UIHandler::onUpdate(MNPCore::Engine &engineContext, MNPCore::GameObject &objContext, const float &deltaTime) {
    if (m_rootcontext->killWindow) {
        engineContext.stop();
    }
    if (m_root != NULL) {
        m_root->update(deltaTime);
    }
}

void UIHandler::onPostUpdate(MNPCore::Engine &engineContext, MNPCore::GameObject &objContext) {
    if (m_root != NULL) {
        m_root->render(engineContext);
    }
}

void UIHandler::onExit(MNPCore::Engine &engineContext, MNPCore::GameObject &objContext) {
    // inputParent->removeReceiver(m_rootcontext);
}

void UIHandler::onUnload(MNPCore::Engine &engineContext, MNPCore::GameObject &objContext) {

}
/*
bool UIHandler::bindRootUI(UIComponent *rootUI) {
    m_root = rootUI;
    m_rootcontext->addContextChild(rootUI->m_context);

    return true;
}
*/
/*
void UIHandler::render(sf::RenderWindow &window){
    if (m_root != NULL) {
        m_root->render(window);
    }
}*/

/*
bool UIButton::receiveEvent(const sf::Event &event, Point offSet) {
    //std::cout << event.type << std::endl;
    if (event.type == sf::Event::MouseButtonPressed){


        if (event.mouseButton.button == sf::Mouse::Left){

            Point mouseClick(event.mouseButton.x,event.mouseButton.y);

            if (collides(mouseClick, offSet)){
                changeColor(sf::Color(std::rand()%255,std::rand()%255,std::rand()%255));
                return true;
            }
        }
    }

    return true;
}*/
/*
UITextInputBox::UITextInputBox(int x,int y,int l,int h,UIClickableContext* context) : UIComponent(x,y,l,h,context),m_context(context) {
    inputText = "";
    focus = false;
};

UITextInputBox::~UITextInputBox(){
    delete m_context;
}
*/
/*
bool UITextInputBox::receiveEvent(const sf::Event &event, Point offSet) {
    std::cout << "\n TEXT WA: " <<inputText << std::endl;
    if (focus==true){

        if ((event.type == sf::Event::KeyPressed)&&(event.key.code == sf::Keyboard::Tilde)){
            focus=true;
            return false;
        }
        else if ((event.type == sf::Event::KeyPressed)&&(event.key.code == sf::Keyboard::BackSpace)){
            if (inputText.size () > 0){
                inputText.resize (inputText.size () - 1);
                return false;

            }

        }
        else if ((event.type == sf::Event::KeyPressed)&&(event.key.code == sf::Keyboard::Return)){
            std::cout << inputText << std::endl;
            return false;

        }
        else if (event.type == sf::Event::TextEntered){
                //std::cout << "You Typed somethn" << std::endl;
            if (event.text.unicode < 128){
                inputText= inputText + static_cast<char>(event.text.unicode);
                return false;
            }
        }
    }

    else{
        if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Tilde)){
            focus=true;
            return false;
        }
    }

    return true;

}*/
/*
void UITextInputBox::receiveRender(sf::RenderWindow &window){}
void UITextInputBox::receiveUpdate(const float &deltaTime){}
*/
