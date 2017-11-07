#pragma once
#include <SFML/Graphics.hpp>

namespace MNPCore {
    class Transform {
        sf::Transform m_transform;
        // flagged whenever this class is potentially updated
        // the first call to getTransform will refresh the xform
        // to properly reflect state
        bool m_isDirty;

        float m_rotation;
        float m_depth;
        sf::Vector2f m_position;
        sf::Vector2f m_scale;

        void updateIfDirty();
    public:
        Transform();

        float &rotation();
        float &depth();
        sf::Vector2f &position();
        sf::Vector2f &scale();

        sf::Vector2f transformPoint(const sf::Vector2f &pt);
        sf::FloatRect transformRect(const sf::FloatRect &rect);
    };
}
