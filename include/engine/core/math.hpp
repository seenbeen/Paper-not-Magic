#pragma once
#include <SFML/Graphics.hpp>

namespace MNPCore {
    struct Quad {
        sf::Vector2f A, B, C, D;
        sf::FloatRect boundingRect;
        Quad(const sf::FloatRect &rect);
        Quad(const sf::Vector2f &A, const sf::Vector2f &B, const sf::Vector2f &C, const sf::Vector2f &D);
        void recalculateBoundingRect();
    };

    class Transform {
        sf::Transform m_transform;
        // flagged whenever this class is potentially updated
        // the first call to getTransform will refresh the xform
        // to properly reflect state
        bool m_isDirty;

        float m_rotation;
        int m_depth;
        sf::Vector2f m_position;
        sf::Vector2f m_scale;

        void updateIfDirty();
    public:
        Transform();

        float &rotation();
        int &depth();
        sf::Vector2f &position();
        sf::Vector2f &scale();

        Quad transformQuad(const Quad &quad);
    };
}
