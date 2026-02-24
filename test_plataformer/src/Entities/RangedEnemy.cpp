#include "Entities/RangedEnemy.hpp"

#include <memory>

#include "Abilities/RangedAbility.hpp"

RangedEnemy::RangedEnemy()
    : Enemy(sf::Color::Yellow, 16.0f) {
    m_stats.health    = 60.0f;
    m_stats.maxHealth = 60.0f;
    m_stats.attack    = 12.0f;
    m_stats.defense   = 5.0f;
    m_stats.speed     = 180.0f;

    addAbility(std::make_unique<RangedAbility>());
}
