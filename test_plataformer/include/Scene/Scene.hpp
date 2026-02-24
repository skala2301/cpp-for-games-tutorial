#pragma once

#include <memory>
#include <vector>

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>

#include "Entities/Enemy.hpp"
#include "Scene/Platform.hpp"
#include "Scene/Tree.hpp"

class Player;

class Scene {
public:
    virtual ~Scene() = default;

    virtual void load() = 0;

    void render(sf::RenderTarget& target) const;

    [[nodiscard]] const std::vector<Platform>& getPlatforms() const noexcept { return m_platforms; }
    [[nodiscard]] std::vector<std::unique_ptr<Enemy>>& getEnemies() noexcept { return m_enemies; }
    [[nodiscard]] const std::vector<std::unique_ptr<Enemy>>& getEnemies() const noexcept { return m_enemies; }
    [[nodiscard]] sf::Vector2f getPlayerSpawn() const noexcept { return m_playerSpawn; }
    [[nodiscard]] sf::FloatRect getLevelBounds() const noexcept { return m_levelBounds; }
    [[nodiscard]] sf::FloatRect getExitZone() const noexcept { return m_exitZone; }

    void setPlayerTarget(const Player* player);

protected:
    std::vector<Platform>                m_platforms;
    std::vector<Tree>                    m_trees;
    std::vector<std::unique_ptr<Enemy>>  m_enemies;
    sf::Vector2f                         m_playerSpawn{100.0f, 500.0f};
    sf::FloatRect                        m_levelBounds{0.0f, 0.0f, 2000.0f, 720.0f};
    sf::FloatRect                        m_exitZone{1900.0f, 0.0f, 100.0f, 720.0f};
};
