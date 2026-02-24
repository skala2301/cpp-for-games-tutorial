#pragma once

#include <cstdint>
#include <unordered_set>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>

class Entity;

enum class AbilityAreaShape : std::uint8_t {
    Circle,
    Arc,
    Rectangle
};

struct AbilityHitArea {
    AbilityAreaShape shape    = AbilityAreaShape::Circle;
    sf::Vector2f     center   = {0.0f, 0.0f};
    float            radius   = 0.0f;
    float            arcAngle = 0.0f;
    sf::Vector2f     direction = {1.0f, 0.0f};
    sf::Vector2f     halfExtents = {0.0f, 0.0f};
};

class Ability {
public:
    virtual ~Ability() = default;

    Ability(float baseDamage, float range, float cooldown,
            float activeDuration, AbilityAreaShape shape,
            float apCost, float attackImpact);

    // Activate — now takes non-const Entity& to spend AP
    [[nodiscard]] bool activate(Entity& owner, sf::Vector2f direction);

    [[nodiscard]] const AbilityHitArea& getHitArea() const noexcept { return m_hitArea; }
    [[nodiscard]] bool isActive() const noexcept { return m_activeTimer > 0.0f; }
    [[nodiscard]] float getBaseDamage() const noexcept { return m_baseDamage; }
    [[nodiscard]] float getRange() const noexcept { return m_range; }
    [[nodiscard]] float getAPCost() const noexcept { return m_apCost; }
    [[nodiscard]] float getAttackImpact() const noexcept { return m_attackImpact; }

    void update(float dt);

    [[nodiscard]] bool overlapsCircle(sf::Vector2f circleCenter, float circleRadius) const;

    void renderDebug(sf::RenderTarget& target) const;

    void clearHitEntities();
    [[nodiscard]] bool hasHitEntity(const Entity* entity) const;
    void markEntityHit(const Entity* entity);

protected:
    virtual void computeHitArea(const Entity& owner, sf::Vector2f direction) = 0;

    float            m_baseDamage;
    float            m_range;
    float            m_cooldown;
    float            m_cooldownTimer   = 0.0f;
    float            m_activeDuration;
    float            m_activeTimer     = 0.0f;
    float            m_apCost;
    float            m_attackImpact;
    AbilityAreaShape m_shape;
    AbilityHitArea   m_hitArea;
    std::unordered_set<const Entity*> m_hitEntities;
};
