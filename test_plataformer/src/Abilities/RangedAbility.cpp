#include "Abilities/RangedAbility.hpp"

#include "Core/Constants.hpp"
#include "Entities/Entity.hpp"

RangedAbility::RangedAbility()
    : Ability(constants::RANGED_BASE_DAMAGE,
              constants::RANGED_RANGE,
              constants::RANGED_COOLDOWN,
              constants::RANGED_ACTIVE_TIME,
              AbilityAreaShape::Rectangle,
              constants::RANGED_AP_COST,
              constants::RANGED_IMPACT) {}

void RangedAbility::computeHitArea(const Entity& owner, sf::Vector2f direction) {
    m_hitArea.shape       = AbilityAreaShape::Rectangle;
    m_hitArea.center      = owner.getPosition() + direction * (m_range * 0.5f);
    m_hitArea.halfExtents = {m_range * 0.5f, 10.0f};
    m_hitArea.direction   = direction;
}
