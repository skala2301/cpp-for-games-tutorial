#pragma once

#include "Abilities/Ability.hpp"

class RangedAbility final : public Ability {
public:
    RangedAbility();

protected:
    void computeHitArea(const Entity& owner, sf::Vector2f direction) override;
};
