#include "Abilities/Ability.hpp"

#include <cmath>

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "Entities/Entity.hpp"

Ability::Ability(float baseDamage, float range, float cooldown,
                 float activeDuration, AbilityAreaShape shape,
                 float apCost, float attackImpact)
    : m_baseDamage(baseDamage)
    , m_range(range)
    , m_cooldown(cooldown)
    , m_activeDuration(activeDuration)
    , m_apCost(apCost)
    , m_attackImpact(attackImpact)
    , m_shape(shape) {}

bool Ability::activate(Entity& owner, sf::Vector2f direction) {
    if (m_cooldownTimer > 0.0f || m_activeTimer > 0.0f) return false;

    // Check AP
    if (owner.getStats().actionPoints < m_apCost) return false;

    owner.getStats().spendAP(m_apCost);
    computeHitArea(owner, direction);
    m_activeTimer = m_activeDuration;
    m_cooldownTimer = m_cooldown;
    m_hitEntities.clear();
    return true;
}

void Ability::update(float dt) {
    if (m_activeTimer > 0.0f) {
        m_activeTimer -= dt;
        if (m_activeTimer <= 0.0f) {
            m_activeTimer = 0.0f;
            m_hitEntities.clear();
        }
    }

    if (m_cooldownTimer > 0.0f) {
        m_cooldownTimer -= dt;
        if (m_cooldownTimer < 0.0f) m_cooldownTimer = 0.0f;
    }
}

bool Ability::overlapsCircle(sf::Vector2f circleCenter, float circleRadius) const {
    if (!isActive()) return false;

    switch (m_hitArea.shape) {
        case AbilityAreaShape::Circle: {
            const float dx = circleCenter.x - m_hitArea.center.x;
            const float dy = circleCenter.y - m_hitArea.center.y;
            const float distSq = dx * dx + dy * dy;
            const float radSum = m_hitArea.radius + circleRadius;
            return distSq <= radSum * radSum;
        }

        case AbilityAreaShape::Arc: {
            // Distance check
            const float dx = circleCenter.x - m_hitArea.center.x;
            const float dy = circleCenter.y - m_hitArea.center.y;
            const float distSq = dx * dx + dy * dy;
            const float radSum = m_hitArea.radius + circleRadius;
            if (distSq > radSum * radSum) return false;

            // Angle check: dot product with direction
            const float dist = std::sqrt(distSq);
            if (dist < 0.001f) return true; // On top of origin

            const float dotProduct = (dx * m_hitArea.direction.x + dy * m_hitArea.direction.y) / dist;
            const float cosAngle = std::cos(m_hitArea.arcAngle * 3.14159265f / 180.0f);
            return dotProduct >= cosAngle;
        }

        case AbilityAreaShape::Rectangle: {
            // AABB vs circle
            const float halfW = m_hitArea.halfExtents.x;
            const float halfH = m_hitArea.halfExtents.y;
            const float closestX = std::max(m_hitArea.center.x - halfW,
                                   std::min(circleCenter.x, m_hitArea.center.x + halfW));
            const float closestY = std::max(m_hitArea.center.y - halfH,
                                   std::min(circleCenter.y, m_hitArea.center.y + halfH));
            const float dx = circleCenter.x - closestX;
            const float dy = circleCenter.y - closestY;
            return (dx * dx + dy * dy) <= circleRadius * circleRadius;
        }
    }

    return false;
}

void Ability::renderDebug(sf::RenderTarget& target) const {
    if (!isActive()) return;

    switch (m_hitArea.shape) {
        case AbilityAreaShape::Circle: {
            sf::CircleShape circle(m_hitArea.radius);
            circle.setOrigin(m_hitArea.radius, m_hitArea.radius);
            circle.setPosition(m_hitArea.center);
            circle.setFillColor(sf::Color(255, 255, 0, 60));
            circle.setOutlineColor(sf::Color(255, 255, 0, 150));
            circle.setOutlineThickness(1.0f);
            target.draw(circle);
            break;
        }
        case AbilityAreaShape::Arc: {
            sf::CircleShape arc(m_hitArea.radius);
            arc.setOrigin(m_hitArea.radius, m_hitArea.radius);
            arc.setPosition(m_hitArea.center);
            arc.setFillColor(sf::Color(255, 200, 0, 50));
            arc.setOutlineColor(sf::Color(255, 200, 0, 120));
            arc.setOutlineThickness(1.0f);
            target.draw(arc);
            break;
        }
        case AbilityAreaShape::Rectangle: {
            sf::RectangleShape rect(m_hitArea.halfExtents * 2.0f);
            rect.setOrigin(m_hitArea.halfExtents);
            rect.setPosition(m_hitArea.center);
            rect.setFillColor(sf::Color(255, 100, 0, 50));
            rect.setOutlineColor(sf::Color(255, 100, 0, 120));
            rect.setOutlineThickness(1.0f);
            target.draw(rect);
            break;
        }
    }
}

void Ability::clearHitEntities() {
    m_hitEntities.clear();
}

bool Ability::hasHitEntity(const Entity* entity) const {
    return m_hitEntities.count(entity) > 0;
}

void Ability::markEntityHit(const Entity* entity) {
    m_hitEntities.insert(entity);
}
