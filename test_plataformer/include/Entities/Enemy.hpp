#pragma once

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "AI/AIController.hpp"
#include "Entities/Entity.hpp"

class Player;

class Enemy : public Entity {
public:
    ~Enemy() override = default;

    void update(float dt) override;
    void render(sf::RenderTarget& target) const override;

    void setTarget(const Player* target) noexcept { m_target = target; }
    [[nodiscard]] const Player* getTarget() const noexcept { return m_target; }
    [[nodiscard]] sf::Vector2f getSpawnPosition() const noexcept { return m_spawnPosition; }
    void setSpawnPosition(sf::Vector2f pos) noexcept { m_spawnPosition = pos; }
    [[nodiscard]] float getPatrolRange() const noexcept { return m_patrolRange; }

    void showHealthBar() noexcept;

protected:
    Enemy(sf::Color color, float radius);

    sf::CircleShape m_shape;
    sf::Color       m_color;
    AIController    m_ai;
    const Player*   m_target = nullptr;
    float           m_patrolRange = 200.0f;
    sf::Vector2f    m_spawnPosition{0.0f, 0.0f};
    float           m_healthBarTimer = 0.0f;
};
