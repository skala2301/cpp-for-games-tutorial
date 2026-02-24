#pragma once

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>

class Projectile {
public:
    Projectile(sf::Vector2f position, sf::Vector2f direction,
               float speed, float damage, float impact,
               float lifetime, float radius);

    void update(float dt);
    void render(sf::RenderTarget& target) const;

    [[nodiscard]] sf::Vector2f getPosition() const noexcept { return m_position; }
    [[nodiscard]] float getRadius() const noexcept { return m_radius; }
    [[nodiscard]] float getDamage() const noexcept { return m_damage; }
    [[nodiscard]] float getImpact() const noexcept { return m_impact; }
    [[nodiscard]] sf::Vector2f getDirection() const noexcept { return m_direction; }
    [[nodiscard]] bool isAlive() const noexcept { return m_lifetime > 0.0f; }

    void kill() noexcept { m_lifetime = 0.0f; }

private:
    sf::Vector2f    m_position;
    sf::Vector2f    m_direction;
    float           m_speed;
    float           m_damage;
    float           m_impact;
    float           m_lifetime;
    float           m_radius;
    sf::CircleShape m_shape;
};
