#include <core/math.hpp>

namespace MNPCore {
    Transform::Transform() {
        m_isDirty = true;
        m_depth = 0.0f;
        m_position = sf::Vector2f(1.0f,1.0f);
        m_rotation = 0.0f;
        m_scale = sf::Vector2f(1.0f,1.0f);
    }

    void Transform::updateIfDirty() {
        if (m_isDirty) {
            m_transform = sf::Transform();
            m_transform.translate(m_position);
            m_transform.scale(m_scale);
            m_transform.rotate(m_rotation);
        }
    }

    float &Transform::rotation() {
        m_isDirty = true;
        return m_rotation;
    }

    // no need to flag depth as dirt, as it doesn't
    // impact the sf::Transform itself
    float &Transform::depth() {
        return m_depth;
    }

    sf::Vector2f &Transform::position() {
        m_isDirty = true;
        return m_position;
    }

    sf::Vector2f &Transform::scale() {
        m_isDirty = true;
        return m_scale;
    }

    sf::Vector2f Transform::transformPoint(const sf::Vector2f &pt) {
        updateIfDirty();
        return m_transform.transformPoint(pt);
    }

    sf::FloatRect Transform::transformRect(const sf::FloatRect &rect) {
        updateIfDirty();
        return m_transform.transformRect(rect);
    }
}
