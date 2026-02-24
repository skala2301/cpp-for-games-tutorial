#include "Entities/Player.hpp"

#include "Abilities/BulletAbility.hpp"
#include "Abilities/MeleeAbility.hpp"
#include "Core/Constants.hpp"

Player::Player() {
    m_stats.health        = constants::PLAYER_HP;
    m_stats.maxHealth     = constants::PLAYER_HP;
    m_stats.attack        = constants::PLAYER_ATTACK;
    m_stats.defense       = constants::PLAYER_DEFENSE;
    m_stats.speed         = constants::PLAYER_SPEED;
    m_stats.actionPoints  = constants::MAX_ACTION_POINTS;
    m_stats.maxActionPoints = constants::MAX_ACTION_POINTS;
    m_stats.recoveryPoints = constants::DEFAULT_RECOVERY_RATE;
    m_collider.radius     = constants::PLAYER_RADIUS;

    m_shape.setRadius(constants::PLAYER_RADIUS);
    m_shape.setOrigin(constants::PLAYER_RADIUS, constants::PLAYER_RADIUS);
    m_shape.setFillColor(sf::Color::Blue);
    m_shape.setOutlineColor(sf::Color(100, 100, 255));
    m_shape.setOutlineThickness(2.0f);

    addAbility(std::make_unique<MeleeAbility>());   // index 0
    addAbility(std::make_unique<BulletAbility>());   // index 1
}

void Player::update(float dt) {
    updateCoyoteTime(dt);
    updateJumpBuffer(dt);
    updateState(dt);
    updateFlash(dt);

    // Flash effect
    if (isFlashing()) {
        m_shape.setFillColor(sf::Color::White);
    } else {
        m_shape.setFillColor(sf::Color::Blue);
    }

    // Apply horizontal movement
    float speed = m_stats.speed;
    if (m_isSprinting) {
        speed *= constants::PLAYER_SPRINT_MULT;
    }
    m_velocity.x = static_cast<float>(m_horizontalInput) * speed;

    // Update facing direction
    if (m_horizontalInput != 0) {
        m_facingRight = (m_horizontalInput > 0);
    }

    // Attack lock
    if (m_attackLockTimer > 0.0f) {
        m_attackLockTimer -= dt;
    }

    m_shape.setPosition(m_position);
}

void Player::render(sf::RenderTarget& target) const {
    target.draw(m_shape);

    // Render active ability debug visualization
    for (const auto& ability : m_abilities) {
        if (ability->isActive()) {
            ability->renderDebug(target);
        }
    }
}

void Player::moveLeft() {
    m_horizontalInput = -1;
}

void Player::moveRight() {
    m_horizontalInput = 1;
}

void Player::stopHorizontal() {
    m_horizontalInput = 0;
}

void Player::jump() {
    if (!m_wantsJump) {
        m_wantsJump = true;
        m_jumpBufferTimer = constants::JUMP_BUFFER_TIME;
    }

    const bool canJump = m_onGround || m_coyoteTimer > 0.0f;

    if (m_wantsJump && canJump) {
        m_velocity.y = -constants::PLAYER_JUMP_FORCE;
        m_onGround = false;
        m_coyoteTimer = 0.0f;
        m_wantsJump = false;
        m_jumpHeld = true;
        m_jumpBufferTimer = 0.0f;
    }
}

void Player::releaseJump() {
    m_wantsJump = false;

    if (m_jumpHeld && m_velocity.y < 0.0f) {
        m_velocity.y *= constants::VARIABLE_JUMP_MULT;
    }
    m_jumpHeld = false;
}

void Player::sprint(bool active) {
    m_isSprinting = active;
}

void Player::attack() {
    if (m_attackLockTimer <= 0.0f && m_activeAbilityIndex < m_abilities.size()) {
        sf::Vector2f dir = m_facingRight ? sf::Vector2f{1.0f, 0.0f} : sf::Vector2f{-1.0f, 0.0f};
        if (m_abilities[m_activeAbilityIndex]->activate(*this, dir)) {
            m_attackLockTimer = 0.15f;
        }
    }
}

void Player::switchAbility() {
    if (m_switchPressed) return; // Debounce
    m_switchPressed = true;

    if (m_abilities.size() > 1) {
        m_activeAbilityIndex = (m_activeAbilityIndex + 1) % m_abilities.size();
    }
}

void Player::updateState(float dt) {
    (void)dt;

    // Reset switch debounce when key is handled externally
    // (InputHandler sets it each frame; release is implicit)

    if (m_attackLockTimer > 0.0f) {
        m_state = PlayerState::Attacking;
        return;
    }

    if (!m_onGround) {
        m_state = (m_velocity.y < 0.0f) ? PlayerState::Jumping : PlayerState::Falling;
    } else if (m_horizontalInput != 0) {
        m_state = m_isSprinting ? PlayerState::Sprinting : PlayerState::Running;
    } else {
        m_state = PlayerState::Idle;
    }
}

void Player::updateCoyoteTime(float dt) {
    if (m_wasOnGround && !m_onGround) {
        m_coyoteTimer = constants::COYOTE_TIME;
    }

    if (m_coyoteTimer > 0.0f) {
        m_coyoteTimer -= dt;
    }

    m_wasOnGround = m_onGround;
}

void Player::updateJumpBuffer(float dt) {
    if (m_jumpBufferTimer > 0.0f) {
        m_jumpBufferTimer -= dt;
    }

    if (m_onGround && m_jumpBufferTimer > 0.0f) {
        m_jumpBufferTimer = 0.0f;
        m_velocity.y = -constants::PLAYER_JUMP_FORCE;
        m_onGround = false;
        m_jumpHeld = true;
    }
}
