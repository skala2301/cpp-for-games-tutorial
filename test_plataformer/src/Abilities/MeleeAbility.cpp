#include "Abilities/MeleeAbility.hpp"

#include "Core/Constants.hpp"
#include "Entities/Entity.hpp"

MeleeAbility::MeleeAbility()
    : Ability(constants::MELEE_BASE_DAMAGE,
              constants::MELEE_RANGE,
              constants::MELEE_COOLDOWN,
              constants::MELEE_ACTIVE_TIME,
              AbilityAreaShape::Arc,
              constants::MELEE_AP_COST,
              constants::MELEE_IMPACT) {}

void MeleeAbility::computeHitArea(const Entity& owner, sf::Vector2f direction) {
    m_hitArea.shape     = AbilityAreaShape::Arc;
    m_hitArea.center    = owner.getPosition();
    m_hitArea.radius    = m_range;
    m_hitArea.arcAngle  = 90.0f; // half-angle -> 180 degree sweep
    m_hitArea.direction = direction;
}
