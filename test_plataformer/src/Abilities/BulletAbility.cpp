#include "Abilities/BulletAbility.hpp"

#include "Core/Constants.hpp"
#include "Entities/Entity.hpp"

BulletAbility::BulletAbility()
    : Ability(constants::BULLET_BASE_DAMAGE,
              constants::BULLET_RANGE,
              constants::BULLET_COOLDOWN,
              constants::BULLET_ACTIVE_TIME,
              AbilityAreaShape::Circle,
              constants::BULLET_AP_COST,
              constants::BULLET_IMPACT) {}

void BulletAbility::computeHitArea(const Entity& owner, sf::Vector2f direction) {
    // The bullet ability itself doesn't have a direct hitbox.
    // Instead it signals the game to spawn a Projectile.
    m_shouldSpawn = true;
    m_spawnDirection = direction;
    m_spawnPosition = owner.getPosition() + direction * (owner.getRadius() + constants::PROJECTILE_RADIUS + 2.0f);

    // Set a minimal hitbox (won't actually be used for damage)
    m_hitArea.shape = AbilityAreaShape::Circle;
    m_hitArea.center = m_spawnPosition;
    m_hitArea.radius = 0.0f;
}
