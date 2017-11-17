#pragma once

#include <engine/input/input-system.hpp>
#include <engine/core/game-object-component.hpp>

namespace MNPInput {
    class InputContextComponent : public MNPInput::InputContext, public MNPCore::GameObjectComponent {
    public:
        // GameObjectComponent
        /*
            Note: Most of these methods are empty, because input contexts generally won't
            need them for the most part. They can still override anyhow in the case that
            they do.
        */
        void onLoad(MNPCore::Engine &engineContext);
        void onEnter(MNPCore::Engine &engineContext);
        void onUpdate(MNPCore::Engine &engineContext, const float &deltaTime);
        void onExit(MNPCore::Engine &engineContext);
        void onUnload(MNPCore::Engine &engineContext);

        // typically will only care about "resetting properties" after everything's gotten a chance
        // to read from the input
        virtual void onPostUpdate(MNPCore::Engine &engineContext) = 0;

        // InputContext
        virtual void handleEvent(const sf::Event &event, bool &willPropagate, bool &wantsFocus) = 0;
    };
}
