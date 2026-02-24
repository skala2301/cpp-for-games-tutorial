#pragma once

#include "Abilities/Ability.hpp"

class MeleeAbility final : public Ability {
public:
    MeleeAbility();

protected:
    void computeHitArea(const Entity& owner, sf::Vector2f direction) override;
};
