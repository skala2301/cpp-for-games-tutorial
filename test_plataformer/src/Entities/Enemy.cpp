#include "Entities/Enemy.hpp"

#include "Core/Constants.hpp"
#include "Entities/Player.hpp"

Enemy::Enemy(sf::Color color, float radius)
    : m_color(color) {
    m_collider.radius = radius;

    m_shape.setRadius(radius);
    m_shape.setOrigin(radius, radius);
    m_shape.setFillColor(color);
    m_shape.setOutlineColor(sf::Color(200, 200, 200));
    m_shape.setOutlineThickness(1.5f);
}

void Enemy::update(float dt) {
    m_ai.update(*this, m_target, dt);
    updateFlash(dt);

    // Flash effect: tint white when hit
    if (isFlashing()) {
        m_shape.setFillColor(sf::Color::White);
    } else {
        m_shape.setFillColor(m_color);
    }

    m_shape.setPosition(m_position);

    if (m_healthBarTimer > 0.0f) {
        m_healthBarTimer -= dt;
    }
}

void Enemy::render(sf::RenderTarget& target) const {
    target.draw(m_shape);

    // Health bar (shown when recently damaged)
    if (m_healthBarTimer > 0.0f) {
        const float barW = constants::HEALTH_BAR_WIDTH;
        const float barH = constants::HEALTH_BAR_HEIGHT;
        const float offsetY = m_collider.radius + constants::HEALTH_BAR_OFFSET_Y;

        // Background (red)
        sf::RectangleShape bg({barW, barH});
        bg.setOrigin(barW * 0.5f, 0.0f);
        bg.setPosition(m_position.x, m_position.y - offsetY - barH);
        bg.setFillColor(sf::Color(180, 30, 30));
        target.draw(bg);

        // Fill (green proportional to HP)
        const float pct = m_stats.health / m_stats.maxHealth;
        sf::RectangleShape fill({barW * pct, barH});
        fill.setOrigin(barW * 0.5f, 0.0f);
        fill.setPosition(m_position.x, m_position.y - offsetY - barH);
        fill.setFillColor(sf::Color(30, 200, 30));
        target.draw(fill);
    }

    // Render active ability debug visualization
    for (const auto& ability : m_abilities) {
        if (ability->isActive()) {
            ability->renderDebug(target);
        }
    }
}

void Enemy::showHealthBar() noexcept {
    m_healthBarTimer = constants::HEALTH_BAR_SHOW_DURATION;
}
