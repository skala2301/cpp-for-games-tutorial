#include "Physics/PhysicsEngine.hpp"

#include <algorithm>

#include "Core/Constants.hpp"
#include "Entities/Enemy.hpp"
#include "Entities/Entity.hpp"
#include "Scene/Platform.hpp"

void PhysicsEngine::update(float deltaTime,
                           Entity& player,
                           std::vector<std::unique_ptr<Enemy>>& enemies,
                           const std::vector<Platform>& platforms) {
    (void)platforms;

    m_accumulator += deltaTime;

    while (m_accumulator >= constants::FIXED_TIMESTEP) {
        // Apply gravity and integrate for player
        applyGravity(player, constants::FIXED_TIMESTEP);
        integrate(player, constants::FIXED_TIMESTEP);
        clampVelocity(player);

        // Apply gravity and integrate for all living enemies
        for (auto& enemy : enemies) {
            if (enemy && enemy->isAlive()) {
                applyGravity(*enemy, constants::FIXED_TIMESTEP);
                integrate(*enemy, constants::FIXED_TIMESTEP);
                clampVelocity(*enemy);
            }
        }

        m_accumulator -= constants::FIXED_TIMESTEP;
    }

    m_alpha = m_accumulator / constants::FIXED_TIMESTEP;
}

void PhysicsEngine::applyGravity(Entity& entity, float dt) const {
    if (!entity.isOnGround()) {
        sf::Vector2f vel = entity.getVelocity();
        vel.y += constants::GRAVITY * dt;
        entity.setVelocity(vel);
    }
}

void PhysicsEngine::integrate(Entity& entity, float dt) const {
    sf::Vector2f pos = entity.getPosition();
    sf::Vector2f vel = entity.getVelocity();
    pos += vel * dt;
    entity.setPosition(pos);
}

void PhysicsEngine::clampVelocity(Entity& entity) const {
    sf::Vector2f vel = entity.getVelocity();
    vel.y = std::min(vel.y, constants::MAX_FALL_SPEED);
    entity.setVelocity(vel);
}
