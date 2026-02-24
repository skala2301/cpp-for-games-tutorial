#include "Abilities/AreaAbility.hpp"

#include "Core/Constants.hpp"
#include "Entities/Entity.hpp"

AreaAbility::AreaAbility()
    : Ability(constants::AREA_BASE_DAMAGE,
              constants::AREA_RANGE,
              constants::AREA_COOLDOWN,
              constants::AREA_ACTIVE_TIME,
              AbilityAreaShape::Circle,
              constants::AREA_AP_COST,
              constants::AREA_IMPACT) {}

void AreaAbility::computeHitArea(const Entity& owner, sf::Vector2f direction) {
    (void)direction;
    m_hitArea.shape  = AbilityAreaShape::Circle;
    m_hitArea.center = owner.getPosition();
    m_hitArea.radius = m_range;
}
