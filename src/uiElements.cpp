#include <mnp/uiElements.hpp>
#include <algorithm>
#include <vector>
#include <SFML/Graphics.hpp>
#include <mnp/shapes.hpp>
#include <iostream>
//Primitives


//UI Components

UIComponent::UIComponent(int x,int y,int l,int h, BaseUIContext* context) : m_rect(x,y,l,h),m_context(context){}

UIComponent::~UIComponent(){

    for (std::list<UIComponent*>::iterator it = m_children.begin(); it != m_children.end(); it++) {
        delete (*it);
    }
}

bool UIComponent::addComponent(UIComponent *newChild) {
    //std::cout <<"Here1"<<std::endl;
    m_children.push_back(newChild);
    //std::cout <<"Here2"<<std::endl;

    m_context->addContextChild(newChild->m_context);
    //std::cout <<"Here3"<<std::endl;
    //sortComponents();
    return true;
}
bool UIComponent::removeComponent(UIComponent *removeChild) {
    for (std::list<UIComponent*>::iterator it = m_children.begin(); it != m_children.end(); it++) {
       if ((*it)==removeChild) {
            //m_children.
            return false;
        }
    }
    return false;
}


void UIComponent::update(sf::Time deltaTime){
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

void UIComponent::render(sf::RenderWindow &window){
    receiveRender(window);

    for (std::list<UIComponent*>::iterator it = m_children.begin(); it != m_children.end(); it++) {
        (*it)->render(window);
    }
}

UIBox::UIBox(int x,int y,int l,int h,BaseUIContext* context) : UIComponent(x,y,l,h,context),m_context(context) {

    m_drawShape = *m_rect.createShape();

    m_drawShape.setFillColor(sf::Color(150, 50, 250));
}
UIBox::~UIBox() {
    //UIComponent::~UIComponent()
    delete(m_context);

}
void UIBox::receiveRender(sf::RenderWindow &window){
    int rX,rY;

    m_rect.getCoord(rX,rY);

    m_drawShape.setPosition((float)rX,(float)rY);
    window.draw(m_drawShape);

}

void UIBox::changeColor(sf::Color newColor){
    m_drawShape.setFillColor(newColor);
}

UIButton::UIButton(int x,int y,int l,int h,UIClickableContext* context) : UIBox(x,y,l,h,context),m_context(context) {
    m_context->setRect(m_rect);
};
UIButton::~UIButton(){}
void UIButton::receiveUpdate(sf::Time deltaTime){

    if (m_context->clicked == true){
        changeColor(sf::Color(std::rand()%255,std::rand()%255,std::rand()%255));

    }
}


UIRoot::UIRoot(int x,int y,int l,int h,BlankContext* context) : UIComponent(x,y,l,h,context),m_context(context) {}

UIRoot::~UIRoot(){
    delete(m_context);
}
void UIRoot::receiveRender(sf::RenderWindow &window){}
void UIRoot::receiveUpdate(sf::Time deltaTime){}



UIHandler::UIHandler(InputHandler* inputParent){
    m_rootcontext = new BlankContext();
    inputParent->addReceiver(m_rootcontext);

}

UIHandler::~UIHandler(){

    if (m_root != NULL){
        delete m_root;
    }
}

bool UIHandler::bindRootUI(UIComponent *rootUI) {
    m_root = rootUI;
    m_rootcontext->addContextChild(rootUI->m_context);

    return true;
}

void UIHandler::update(sf::Time deltaTime) {
    if (m_root != NULL) {

        m_root->update(deltaTime);
    }
}


void UIHandler::render(sf::RenderWindow &window){
    if (m_root != NULL) {

        m_root->render(window);
    }

}


/*
bool UIButton::receiveEvent(sf::Event *event, Point offSet) {
    //std::cout << event->type << std::endl;
    if (event->type == sf::Event::MouseButtonPressed){


        if (event->mouseButton.button == sf::Mouse::Left){

            Point mouseClick(event->mouseButton.x,event->mouseButton.y);

            if (collides(mouseClick, offSet)){
                changeColor(sf::Color(std::rand()%255,std::rand()%255,std::rand()%255));
                return true;
            }
        }
    }

    return true;
}*/




UITextInputBox::UITextInputBox(int x,int y,int l,int h,UIClickableContext* context) : UIComponent(x,y,l,h,context),m_context(context) {
    inputText = "";
    focus = false;
};

UITextInputBox::~UITextInputBox(){
    delete(m_context);
}
/*
bool UITextInputBox::receiveEvent(sf::Event *event, Point offSet) {
    std::cout << "\n TEXT WA: " <<inputText << std::endl;
    if (focus==true){

        if ((event->type == sf::Event::KeyPressed)&&(event->key.code == sf::Keyboard::Tilde)){
            focus=true;
            return false;
        }
        else if ((event->type == sf::Event::KeyPressed)&&(event->key.code == sf::Keyboard::BackSpace)){
            if (inputText.size () > 0){
                inputText.resize (inputText.size () - 1);
                return false;

            }

        }
        else if ((event->type == sf::Event::KeyPressed)&&(event->key.code == sf::Keyboard::Return)){
            std::cout << inputText << std::endl;
            return false;

        }
        else if (event->type == sf::Event::TextEntered){
                //std::cout << "You Typed somethn" << std::endl;
            if (event->text.unicode < 128){
                inputText= inputText + static_cast<char>(event->text.unicode);
                return false;
            }
        }
    }

    else{
        if ((event->type == sf::Event::KeyPressed) && (event->key.code == sf::Keyboard::Tilde)){
            focus=true;
            return false;
        }
    }

    return true;

}*/

void UITextInputBox::receiveRender(sf::RenderWindow &window){



}
void UITextInputBox::receiveUpdate(sf::Time deltaTime){

}
