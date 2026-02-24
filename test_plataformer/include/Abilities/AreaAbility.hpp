#pragma once

#include "Abilities/Ability.hpp"

class AreaAbility final : public Ability {
public:
    AreaAbility();

protected:
    void computeHitArea(const Entity& owner, sf::Vector2f direction) override;
};
