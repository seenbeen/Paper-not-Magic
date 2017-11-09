#pragma once
#include <engine/core/stage.hpp>

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
}
