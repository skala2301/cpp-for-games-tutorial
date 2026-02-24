#pragma once

#include <cstdint>

#include <SFML/System/Vector2.hpp>

class Enemy;
class Player;

enum class AIState : std::uint8_t {
    Idle,
    Patrol,
    Chase,
    Attack,
    Retreat
};

class AIController {
public:
    void update(Enemy& owner, const Player* target, float dt);

    [[nodiscard]] AIState getState() const noexcept { return m_state; }

private:
    void executeIdle(Enemy& owner, float dt);
    void executePatrol(Enemy& owner, float dt);
    void executeChase(Enemy& owner, const Player& target, float dt);
    void executeAttack(Enemy& owner, const Player& target, float dt);
    void executeRetreat(Enemy& owner, const Player& target, float dt);

    [[nodiscard]] float distanceTo(sf::Vector2f a, sf::Vector2f b) const noexcept;

    AIState m_state           = AIState::Idle;
    float   m_stateTimer      = 0.0f;
    float   m_patrolDirection = 1.0f;
};
