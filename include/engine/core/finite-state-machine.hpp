#pragma once
#include <cstdlib>
#include <map>
#include <vector>

namespace MNPCore {
    template <class T, typename StateEnum> class FSM;

    template <class T, typename StateEnum>
    class FSMState {
    template <class _T, typename _StateEnum> friend class FSM;
        FSM<T,StateEnum> *m_fsm;
        const StateEnum m_stateEnum;

    protected:
        void changeState(StateEnum stateEnum) {
            m_fsm->changeState(stateEnum);
        }

        void bindFSM(FSM<T,StateEnum> *fsm) {
            m_fsm = fsm;
        }

        virtual void enter(T &contextObject) = 0;
        virtual void update(T &contextObject) = 0;
        virtual void exit(T &contextObject) = 0;

    public:
        FSMState(StateEnum stateEnum) : m_fsm(NULL), m_stateEnum(stateEnum) {}
        virtual ~FSMState() {}

        StateEnum getStateEnum() {
            return m_stateEnum;
        }
    };

    template <class T>
    class BaseFSM {
    protected:
        virtual ~BaseFSM() {};
    public:
        virtual void destroy(T &contextObject) = 0;
        virtual void update(T &contextObject) = 0;
    };

    template<class T, typename StateEnum>
    class FSM : public BaseFSM<T> {
        std::map<StateEnum, FSMState<T, StateEnum>*> m_stateMap;
        FSMState<T, StateEnum> *m_nextState;
        FSMState<T, StateEnum> *m_currentState;

    protected:
        // must destroy through destroy func
        ~FSM() {
            // clean up all fsmstates; context object doesn't belong to us so dw about it
            typename std::map<StateEnum, FSMState<T, StateEnum>*>::iterator it;
            for (it = m_stateMap.begin(); it != m_stateMap.end(); ++it) {
                delete it->second;
            }
            // map cleans itself up, no need to erase pointers
        }

    public:
        FSM(std::vector<FSMState<T,StateEnum>*> &states, StateEnum startState) {
            for (unsigned int i = 0; i < states.size(); ++i) {
                m_stateMap[states[i]->getStateEnum()] = states[i];
                states[i]->bindFSM(this);
            }
            m_currentState = NULL;
            m_nextState = m_stateMap.find(startState)->second;
        }

        void destroy(T &contextObject) {
            // first, give the current state a chance to exit
            if (m_currentState != NULL) {
                m_currentState->exit(contextObject);
                m_currentState = NULL;
            } else {
                // warn!
            }

            delete this;
        }

        void changeState(StateEnum state) {
            m_nextState = m_stateMap.find(state)->second;
        }

        void update(T &contextObject) {
            if (m_currentState != m_nextState) {
                if (m_currentState != NULL) {
                    m_currentState->exit(contextObject);
                }
                m_currentState = m_nextState;
                m_currentState->enter(contextObject);
            }
            m_currentState->update(contextObject);
        }
    };
}
