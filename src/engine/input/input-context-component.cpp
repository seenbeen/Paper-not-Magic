#include <engine/input/input-system.hpp>
#include <engine/core/game-object-component.hpp>

#include <engine/input/input-context-component.hpp>

namespace MNPInput {
    using MNPCore::Engine;
    using MNPCore::GameObject;

    void InputContextComponent::onLoad(Engine &engineContext) {}
    void InputContextComponent::onEnter(Engine &engineContext) {}
    void InputContextComponent::onUpdate(Engine &engineContext, const float &deltaTime) {}
    void InputContextComponent::onExit(Engine &engineContext) {}
    void InputContextComponent::onUnload(Engine &engineContext) {}
}

