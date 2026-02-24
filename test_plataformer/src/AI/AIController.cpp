#include "AI/AIController.hpp"

#include <cmath>

#include "Core/Constants.hpp"
#include "Entities/Enemy.hpp"
#include "Entities/Player.hpp"

void AIController::update(Enemy& owner, const Player* target, float dt) {
    m_stateTimer += dt;

    if (target == nullptr || !target->isAlive()) {
        if (m_state != AIState::Idle && m_state != AIState::Patrol) {
            m_state = AIState::Idle;
            m_stateTimer = 0.0f;
        }
    }

    switch (m_state) {
        case AIState::Idle:
            executeIdle(owner, dt);
            if (target && target->isAlive()) {
                float dist = distanceTo(owner.getPosition(), target->getPosition());
                if (dist < constants::ENEMY_DETECT_RANGE) {
                    m_state = AIState::Chase;
                    m_stateTimer = 0.0f;
                }
            }
            break;

        case AIState::Patrol:
            executePatrol(owner, dt);
            if (target && target->isAlive()) {
                float dist = distanceTo(owner.getPosition(), target->getPosition());
                if (dist < constants::ENEMY_DETECT_RANGE) {
                    m_state = AIState::Chase;
                    m_stateTimer = 0.0f;
                }
            }
            break;

        case AIState::Chase:
            if (target && target->isAlive()) {
                executeChase(owner, *target, dt);
            } else {
                m_state = AIState::Patrol;
                m_stateTimer = 0.0f;
            }
            break;

        case AIState::Attack:
            if (target && target->isAlive()) {
                executeAttack(owner, *target, dt);
            } else {
                m_state = AIState::Idle;
                m_stateTimer = 0.0f;
            }
            break;

        case AIState::Retreat:
            if (target && target->isAlive()) {
                executeRetreat(owner, *target, dt);
            } else {
                m_state = AIState::Idle;
                m_stateTimer = 0.0f;
            }
            break;
    }
}

void AIController::executeIdle(Enemy& owner, float dt) {
    (void)dt;
    // Stand still
    owner.setVelocity({0.0f, owner.getVelocity().y});

    if (m_stateTimer >= constants::IDLE_DURATION) {
        m_state = AIState::Patrol;
        m_stateTimer = 0.0f;
    }
}

void AIController::executePatrol(Enemy& owner, float dt) {
    (void)dt;

    const float speed = owner.getStats().speed * 0.5f;
    sf::Vector2f vel = owner.getVelocity();
    vel.x = m_patrolDirection * speed;
    owner.setVelocity(vel);
    owner.setFacingRight(m_patrolDirection > 0.0f);

    // Check patrol range
    const float distFromSpawn = owner.getPosition().x - owner.getSpawnPosition().x;
    if (std::abs(distFromSpawn) > owner.getPatrolRange()) {
        m_patrolDirection = -m_patrolDirection;
    }

    if (m_stateTimer >= constants::PATROL_DURATION) {
        m_state = AIState::Idle;
        m_stateTimer = 0.0f;
    }
}

void AIController::executeChase(Enemy& owner, const Player& target, float dt) {
    (void)dt;

    const float dist = distanceTo(owner.getPosition(), target.getPosition());

    // Lose interest
    if (dist > constants::ENEMY_LOSE_RANGE) {
        m_state = AIState::Patrol;
        m_stateTimer = 0.0f;
        return;
    }

    // Check if in attack range
    const float attackRange = owner.getAbilities().empty() ? 50.0f : owner.getAbilities()[0]->getRange();
    if (dist < attackRange) {
        m_state = AIState::Attack;
        m_stateTimer = 0.0f;
        return;
    }

    // Move toward player
    const float dir = (target.getPosition().x > owner.getPosition().x) ? 1.0f : -1.0f;
    sf::Vector2f vel = owner.getVelocity();
    vel.x = dir * owner.getStats().speed;
    owner.setVelocity(vel);
    owner.setFacingRight(dir > 0.0f);
}

void AIController::executeAttack(Enemy& owner, const Player& target, float dt) {
    (void)dt;

    // Face the player
    const float dir = (target.getPosition().x > owner.getPosition().x) ? 1.0f : -1.0f;
    owner.setFacingRight(dir > 0.0f);

    // Stop moving while attacking
    sf::Vector2f vel = owner.getVelocity();
    vel.x = 0.0f;
    owner.setVelocity(vel);

    // Use ability
    if (!owner.getAbilities().empty()) {
        sf::Vector2f abilityDir = {dir, 0.0f};
        owner.useAbility(0, abilityDir);
    }

    const float dist = distanceTo(owner.getPosition(), target.getPosition());
    const float attackRange = owner.getAbilities().empty() ? 50.0f : owner.getAbilities()[0]->getRange();

    if (dist > attackRange * 1.5f) {
        m_state = AIState::Chase;
        m_stateTimer = 0.0f;
    }
}

void AIController::executeRetreat(Enemy& owner, const Player& target, float dt) {
    (void)dt;

    // Move away from player
    const float dir = (target.getPosition().x > owner.getPosition().x) ? -1.0f : 1.0f;
    sf::Vector2f vel = owner.getVelocity();
    vel.x = dir * owner.getStats().speed;
    owner.setVelocity(vel);
    owner.setFacingRight(dir > 0.0f);

    if (m_stateTimer >= constants::RETREAT_DURATION) {
        m_state = AIState::Chase;
        m_stateTimer = 0.0f;
    }
}

float AIController::distanceTo(sf::Vector2f a, sf::Vector2f b) const noexcept {
    const float dx = a.x - b.x;
    const float dy = a.y - b.y;
    return std::sqrt(dx * dx + dy * dy);
}
