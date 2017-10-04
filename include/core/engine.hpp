#pragma once
#include <vector>

#include <core/finitestatemachine.hpp>
#include <core/stage.hpp>

namespace MNPCore {
    class Engine;

    class BaseEngineConfig {
    friend class Engine;

    virtual BaseFSM<Engine> *makeFSM() = 0;

    public:
        virtual ~BaseEngineConfig() {}
    };

    template <typename StageEnum>
    class EngineConfig : public BaseEngineConfig {
        StageEnum m_start;
        std::vector<FSMState<Engine, StageEnum>*> m_engineStages;

        BaseFSM<Engine> *makeFSM() {
            return new FSM<Engine,StageEnum>(m_engineStages, m_start);
        }
    public:
        EngineConfig(StageEnum start, std::vector<Stage<StageEnum>*> &engineStages)
            : m_start(start) {
            for (unsigned int i = 0; i < engineStages.size(); ++i) {
                m_engineStages.push_back(engineStages[i]);
            }
            engineStages.clear();
        }
    };

    class Engine {
        bool m_isInitialized;
        bool m_isRunning;
        BaseFSM<Engine> *m_fsm;

    public:
        // expose some getters to access engine modules

        Engine();
        void initialize(BaseEngineConfig *config);
        void run();
        void stop();
        void shutdown();
    };
}
