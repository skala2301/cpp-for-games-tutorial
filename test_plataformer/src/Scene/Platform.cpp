#include "Scene/Platform.hpp"

Platform::Platform(sf::Vector2f position, sf::Vector2f size, PlatformType type)
    : m_type(type) {
    m_shape.setPosition(position);
    m_shape.setSize(size);
    m_aabb = AABB::fromRect(position, size);

    switch (type) {
        case PlatformType::Floor:
            m_shape.setFillColor(sf::Color(120, 100, 80)); // brown-grey
            m_shape.setOutlineColor(sf::Color(90, 75, 60));
            break;
        case PlatformType::Wall:
            m_shape.setFillColor(sf::Color(100, 130, 100)); // grey-green
            m_shape.setOutlineColor(sf::Color(80, 110, 80));
            break;
    }
    m_shape.setOutlineThickness(1.0f);
}

void Platform::render(sf::RenderTarget& target) const {
    target.draw(m_shape);
}
