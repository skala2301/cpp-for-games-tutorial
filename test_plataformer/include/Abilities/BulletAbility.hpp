#pragma once

#include <SFML/System/Vector2.hpp>

#include "Abilities/Ability.hpp"

class BulletAbility final : public Ability {
public:
    BulletAbility();

    // Projectile spawn request pattern
    [[nodiscard]] bool shouldSpawnProjectile() const noexcept { return m_shouldSpawn; }
    [[nodiscard]] sf::Vector2f getSpawnDirection() const noexcept { return m_spawnDirection; }
    [[nodiscard]] sf::Vector2f getSpawnPosition() const noexcept { return m_spawnPosition; }
    void consumeSpawnRequest() noexcept { m_shouldSpawn = false; }

protected:
    void computeHitArea(const Entity& owner, sf::Vector2f direction) override;

private:
    bool         m_shouldSpawn = false;
    sf::Vector2f m_spawnDirection{1.0f, 0.0f};
    sf::Vector2f m_spawnPosition{0.0f, 0.0f};
};
