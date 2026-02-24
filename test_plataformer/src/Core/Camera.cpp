#include "Core/Camera.hpp"

#include <algorithm>

#include "Core/Constants.hpp"

Camera::Camera(sf::Vector2f viewSize) {
    m_view.setSize(viewSize);
    m_view.setCenter(viewSize * 0.5f);
}

void Camera::update(sf::Vector2f targetPos, bool facingRight, float dt) {
    const float lookAhead = facingRight ? constants::CAMERA_LOOK_AHEAD
                                        : -constants::CAMERA_LOOK_AHEAD;
    sf::Vector2f desired = {targetPos.x + lookAhead, targetPos.y};

    sf::Vector2f current = m_view.getCenter();
    sf::Vector2f newCenter = current + (desired - current) * (constants::CAMERA_LERP_SPEED * dt);

    // Clamp to level bounds
    if (m_hasBounds) {
        const float halfW = m_view.getSize().x * 0.5f;
        const float halfH = m_view.getSize().y * 0.5f;

        newCenter.x = std::clamp(newCenter.x,
                                 m_levelBounds.left + halfW,
                                 m_levelBounds.left + m_levelBounds.width - halfW);
        newCenter.y = std::clamp(newCenter.y,
                                 m_levelBounds.top + halfH,
                                 m_levelBounds.top + m_levelBounds.height - halfH);
    }

    m_view.setCenter(newCenter);
}

void Camera::setLevelBounds(sf::FloatRect bounds) {
    m_levelBounds = bounds;
    m_hasBounds = true;
}

void Camera::snapTo(sf::Vector2f position) {
    m_view.setCenter(position);
}
