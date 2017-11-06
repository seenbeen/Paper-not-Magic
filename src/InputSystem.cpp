#include <SFML/Graphics.hpp>
#include <mnp/InputSystem.hpp>
#include <list>
#include <iostream>



bool InputHandler::addReceiver(InputContext *newReceiver){
    m_receivers.push_back(newReceiver);
    return true;

}

void InputHandler::sendEvent(sf::Event *event){
    if (event->type == sf::Event::MouseButtonPressed){
        std::cout << "Handler Received Click" <<std::endl;
    }

    std::list<InputContext*>::iterator it = m_receivers.begin();
    while(it != m_receivers.end() && (*it)->propogateToChildren(event)){
        it++;
    }


}
void InputHandler::update(sf::Time deltaTime){
    for (std::list<InputContext*>::iterator it = m_receivers.begin(); it != m_receivers.end(); it++) {
        (*it)->propogateUpdate(deltaTime);
    }
}

bool InputContext::addContextChild(InputContext *newChild){
    m_children.push_back(newChild);
    return true;
}



bool InputContext::propogateToChildren(sf::Event *event){
    if (handleInput(event) == false){
        return false;
    };
    for (std::list<InputContext*>::iterator it = m_children.begin(); it != m_children.end(); it++) {
       if ((*it)->InputContext::propogateToChildren(event) == false) {
            InputContext* temp = *it;
            if (temp->wantsFocus(event)){
                m_children.erase(it);
                m_children.push_front(temp);
            }
            return false;
       }
    }
    return true;
}
void InputContext::propogateUpdate(sf::Time deltaTime){
    update(deltaTime);
    for (std::list<InputContext*>::iterator it = m_children.begin(); it != m_children.end(); it++) {
        (*it)->propogateUpdate(deltaTime);
    }
}

bool BaseUIContext::wantsFocus(sf::Event* event){
    focusFlag = wantsFocusImpl(event);
    return focusFlag;
}

bool BaseUIContext::getFocus(){
    if (focusFlag){
        focusFlag = false;
        return true;
    }
    return false;
}

bool UIClickableContext::wantsFocusImpl(sf::Event *event){
    return true;
}

bool UIClickableContext::handleInput(sf::Event *event){
    if (event->type == sf::Event::MouseButtonPressed){
        if (event->mouseButton.button == sf::Mouse::Left){
            if (m_MyRect.collide(event->mouseButton.x,event->mouseButton.y)){
                clicked=true;
                return false;
            }
        }
    }
    return true;

}

bool BlankContext::handleInput(sf::Event* event){
    return true;
}

void BlankContext::update(sf::Time deltaTime){}

bool BlankContext::wantsFocusImpl(sf::Event* event){
    return false;
}
void UIClickableContext::update(sf::Time deltaTime){
    clicked = false;
}

void UIClickableContext::setRect(Rectangle r){
    m_MyRect = r;
}

InputContext::InputContext(){}
InputContext::~InputContext(){}

UIClickableContext::UIClickableContext(){clicked=false;}
UIClickableContext::~UIClickableContext(){}
