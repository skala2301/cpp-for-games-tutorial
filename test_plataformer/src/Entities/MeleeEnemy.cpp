#include "Entities/MeleeEnemy.hpp"

#include <memory>

#include "Abilities/MeleeAbility.hpp"

MeleeEnemy::MeleeEnemy()
    : Enemy(sf::Color::Red, 18.0f) {
    m_stats.health    = 80.0f;
    m_stats.maxHealth = 80.0f;
    m_stats.attack    = 15.0f;
    m_stats.defense   = 10.0f;
    m_stats.speed     = 150.0f;

    addAbility(std::make_unique<MeleeAbility>());
}
