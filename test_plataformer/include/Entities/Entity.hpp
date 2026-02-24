#pragma once

#include <algorithm>
#include <cstdint>
#include <memory>
#include <vector>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>

#include "Abilities/Ability.hpp"

struct Stats {
    float health    = 100.0f;
    float maxHealth = 100.0f;
    float attack    = 10.0f;
    float defense   = 8.0f;
    float speed     = 250.0f;

    // Action Points
    float actionPoints    = 100.0f;
    float maxActionPoints = 100.0f;
    float recoveryPoints  = 20.0f; // AP recovered per second

    [[nodiscard]] bool isAlive() const noexcept { return health > 0.0f; }
    [[nodiscard]] bool isExhausted() const noexcept { return actionPoints <= 0.0f; }

    void takeDamage(float rawDamage) noexcept {
        const float reduction = defense / (defense + 100.0f);
        const float effective = rawDamage * (1.0f - reduction);
        health -= effective;
        if (health < 0.0f) health = 0.0f;
    }

    void spendAP(float cost) noexcept {
        actionPoints -= cost;
        if (actionPoints < 0.0f) actionPoints = 0.0f;
    }

    void recoverAP(float dt) noexcept {
        actionPoints += recoveryPoints * dt;
        if (actionPoints > maxActionPoints) actionPoints = maxActionPoints;
    }
};

struct CircleCollider {
    float radius = 20.0f;
    sf::Vector2f offset{0.0f, 0.0f};
};

class Entity {
public:
    virtual ~Entity() = default;

    Entity(const Entity&) = delete;
    Entity& operator=(const Entity&) = delete;
    Entity(Entity&&) = default;
    Entity& operator=(Entity&&) = default;

    virtual void update(float dt) = 0;
    virtual void render(sf::RenderTarget& target) const = 0;

    // Transform
    [[nodiscard]] sf::Vector2f getPosition() const noexcept { return m_position; }
    void setPosition(sf::Vector2f pos) noexcept { m_position = pos; }
    [[nodiscard]] sf::Vector2f getVelocity() const noexcept { return m_velocity; }
    void setVelocity(sf::Vector2f vel) noexcept { m_velocity = vel; }
    [[nodiscard]] bool isFacingRight() const noexcept { return m_facingRight; }
    void setFacingRight(bool right) noexcept { m_facingRight = right; }

    // Stats
    [[nodiscard]] const Stats& getStats() const noexcept { return m_stats; }
    [[nodiscard]] Stats& getStats() noexcept { return m_stats; }
    [[nodiscard]] bool isAlive() const noexcept { return m_stats.isAlive(); }

    // Collider
    [[nodiscard]] const CircleCollider& getCollider() const noexcept { return m_collider; }
    [[nodiscard]] float getRadius() const noexcept { return m_collider.radius; }

    // Ground state
    [[nodiscard]] bool isOnGround() const noexcept { return m_onGround; }
    void setOnGround(bool grounded) noexcept { m_onGround = grounded; }

    // Flash effect (impact)
    void triggerFlash() noexcept { m_flashTimer = 0.1f; }
    [[nodiscard]] bool isFlashing() const noexcept { return m_flashTimer > 0.0f; }
    void updateFlash(float dt) noexcept { if (m_flashTimer > 0.0f) m_flashTimer -= dt; }

    // Abilities
    void addAbility(std::unique_ptr<Ability> ability);
    [[nodiscard]] const std::vector<std::unique_ptr<Ability>>& getAbilities() const noexcept;
    [[nodiscard]] std::vector<std::unique_ptr<Ability>>& getAbilities() noexcept;
    void useAbility(std::size_t index, sf::Vector2f direction);
    void updateAbilityCooldowns(float dt);

protected:
    Entity() = default;

    sf::Vector2f m_position{0.0f, 0.0f};
    sf::Vector2f m_velocity{0.0f, 0.0f};
    bool         m_facingRight = true;
    Stats        m_stats;
    CircleCollider m_collider;
    bool         m_onGround = false;
    float        m_flashTimer = 0.0f;
    std::vector<std::unique_ptr<Ability>> m_abilities;
};
