#include <list>
#include <iostream>

#include <SFML/Graphics.hpp>

#include <engine/input/input-system.hpp>

namespace MNPInput {
    InputHandler::InputHandler() {}

    InputHandler::~InputHandler() {}

    bool InputHandler::addContext(InputContext *context){
        m_contextRoot.addContextChild(context);
        return true;
    }

    void InputHandler::sendEvent(const sf::Event &event){
        bool willPropagate = true, wantsFocus = false;
        m_contextRoot.propagateEvent(event, willPropagate, wantsFocus);
    }

    InputContext::InputContext(){}
    InputContext::~InputContext(){
        std::list<InputContext*>::iterator it;
        for (it = m_children.begin(); it != m_children.end(); ++it) {
            delete *it;
        }
        m_children.clear();
    }

    bool InputContext::addContextChild(InputContext *newChild){
        m_children.push_back(newChild);
        return true;
    }

    void InputContext::propagateEvent(const sf::Event &event, bool &willPropagate, bool &wantsFocus){
        handleEvent(event, willPropagate, wantsFocus);

        if (!willPropagate) { // means we wern't hit; no point in testing kids
            return;
        }

        // the contexts that want to be moved to the front of the priority list
        std::list<InputContext*>::iterator it, tmp;
        bool childWillPropagate = true;
        it = m_children.begin();

        while (it != m_children.end()) {
            (*it)->propagateEvent(event, childWillPropagate, wantsFocus);
            if (wantsFocus) {
                tmp = it;
                ++tmp;
                m_children.push_front(*it);
                m_children.erase(it);
                it = tmp;
            } else {
                ++it;
            }
            if (childWillPropagate) {
                break;
            }
        }
    }

    void PassThroughContext::handleEvent(const sf::Event &event, bool &willPropagate, bool &wantsFocus) {
        willPropagate = true;
        wantsFocus = false;
    }
}
