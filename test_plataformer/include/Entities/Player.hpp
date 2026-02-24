#pragma once

#include <cstddef>
#include <cstdint>

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "Entities/Entity.hpp"

enum class PlayerState : std::uint8_t {
    Idle,
    Running,
    Sprinting,
    Jumping,
    Falling,
    Attacking
};

class Player final : public Entity {
public:
    Player();

    void update(float dt) override;
    void render(sf::RenderTarget& target) const override;

    void moveLeft();
    void moveRight();
    void stopHorizontal();
    void jump();
    void releaseJump();
    void sprint(bool active);
    void attack();
    void switchAbility();
    void releaseSwitchAbility() noexcept { m_switchPressed = false; }

    [[nodiscard]] PlayerState getState() const noexcept { return m_state; }
    [[nodiscard]] std::size_t getActiveAbilityIndex() const noexcept { return m_activeAbilityIndex; }

private:
    void updateState(float dt);
    void updateCoyoteTime(float dt);
    void updateJumpBuffer(float dt);

    PlayerState     m_state = PlayerState::Idle;
    sf::CircleShape m_shape;

    bool  m_wantsJump       = false;
    bool  m_isSprinting     = false;
    float m_coyoteTimer     = 0.0f;
    float m_jumpBufferTimer = 0.0f;
    bool  m_jumpHeld        = false;
    bool  m_wasOnGround     = false;
    float m_attackLockTimer = 0.0f;
    int   m_horizontalInput = 0;

    std::size_t m_activeAbilityIndex = 0;
    bool        m_switchPressed = false;
};
