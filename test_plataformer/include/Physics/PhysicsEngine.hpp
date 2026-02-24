#pragma once

#include <memory>
#include <vector>

class Entity;
class Enemy;
class Platform;

class PhysicsEngine {
public:
    void update(float deltaTime,
                Entity& player,
                std::vector<std::unique_ptr<Enemy>>& enemies,
                const std::vector<Platform>& platforms);

    [[nodiscard]] float getAlpha() const noexcept { return m_alpha; }

private:
    void applyGravity(Entity& entity, float dt) const;
    void integrate(Entity& entity, float dt) const;
    void clampVelocity(Entity& entity) const;

    float m_accumulator = 0.0f;
    float m_alpha       = 0.0f;
};
