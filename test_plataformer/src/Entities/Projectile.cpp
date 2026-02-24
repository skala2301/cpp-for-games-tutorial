#include "Entities/Projectile.hpp"

Projectile::Projectile(sf::Vector2f position, sf::Vector2f direction,
                       float speed, float damage, float impact,
                       float lifetime, float radius)
    : m_position(position)
    , m_direction(direction)
    , m_speed(speed)
    , m_damage(damage)
    , m_impact(impact)
    , m_lifetime(lifetime)
    , m_radius(radius) {
    m_shape.setRadius(radius);
    m_shape.setOrigin(radius, radius);
    m_shape.setFillColor(sf::Color::Cyan);
    m_shape.setOutlineColor(sf::Color::White);
    m_shape.setOutlineThickness(1.0f);
    m_shape.setPosition(position);
}

void Projectile::update(float dt) {
    m_position += m_direction * m_speed * dt;
    m_shape.setPosition(m_position);
    m_lifetime -= dt;
}

void Projectile::render(sf::RenderTarget& target) const {
    target.draw(m_shape);
}
