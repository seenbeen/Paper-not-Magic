#include <engine/core/math.hpp>

namespace MNPCore {
    Quad::Quad(const sf::FloatRect &rect) {
        A = sf::Vector2f(rect.left,rect.top);
        B = sf::Vector2f(rect.left+rect.width,rect.top);
        C = sf::Vector2f(rect.left+rect.width,rect.top+rect.height);
        D = sf::Vector2f(rect.left,rect.top+rect.height);
        recalculateBoundingRect();
    }

    Quad::Quad(const sf::Vector2f &A, const sf::Vector2f &B, const sf::Vector2f &C, const sf::Vector2f &D)
        : A(A), B(B), C(C), D(D){
        recalculateBoundingRect();
    }

    void Quad::recalculateBoundingRect() {
        sf::Vector2f *pts[4] = { &A, &B, &C, &D };
        sf::Vector2f topLeft = *pts[0];
        sf::Vector2f bottomRight = *pts[0];
        for (int i = 0; i < 4; ++i) {
            topLeft.x = std::min(topLeft.x,pts[i]->x);
            topLeft.y = std::min(topLeft.y,pts[i]->y);
            bottomRight.x = std::max(bottomRight.x,pts[i]->x);
            bottomRight.y = std::max(bottomRight.y,pts[i]->y);
        }
        boundingRect.left = topLeft.x;
        boundingRect.top = topLeft.y;
        boundingRect.width = bottomRight.x-topLeft.x;
        boundingRect.height = bottomRight.y-topLeft.y;
    }

    Transform::Transform() {
        m_isDirty = true;
        m_depth = 0;
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
    int &Transform::depth() {
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

    Quad Transform::transformQuad(const Quad &quad) {
        updateIfDirty();
        return Quad(m_transform.transformPoint(quad.A),m_transform.transformPoint(quad.B),
                    m_transform.transformPoint(quad.C),m_transform.transformPoint(quad.D));
    }
}
