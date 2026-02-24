#include "Entities/TankEnemy.hpp"

#include <memory>

#include "Abilities/AreaAbility.hpp"

TankEnemy::TankEnemy()
    : Enemy(sf::Color::Black, 24.0f) {
    m_stats.health    = 150.0f;
    m_stats.maxHealth = 150.0f;
    m_stats.attack    = 8.0f;
    m_stats.defense   = 30.0f;
    m_stats.speed     = 100.0f;

    m_shape.setOutlineColor(sf::Color(80, 80, 80));
    m_shape.setOutlineThickness(2.0f);

    addAbility(std::make_unique<AreaAbility>());
}
