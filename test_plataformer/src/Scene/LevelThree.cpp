#include "Scene/LevelThree.hpp"

#include <memory>

#include "Entities/MeleeEnemy.hpp"
#include "Entities/RangedEnemy.hpp"
#include "Entities/TankEnemy.hpp"

void LevelThree::load() {
    m_platforms.clear();
    m_trees.clear();
    m_enemies.clear();

    // Level bounds - wide arena
    m_levelBounds = {0.0f, 0.0f, 2500.0f, 800.0f};
    m_playerSpawn = {150.0f, 550.0f};
    m_exitZone    = {2300.0f, 400.0f, 200.0f, 220.0f};

    // ---- Ground (arena floor) ----
    m_platforms.emplace_back(sf::Vector2f{0.0f, 620.0f}, sf::Vector2f{2500.0f, 180.0f}, PlatformType::Floor);

    // ---- Pillars (walls for cover) ----
    m_platforms.emplace_back(sf::Vector2f{400.0f, 420.0f}, sf::Vector2f{40.0f, 200.0f}, PlatformType::Wall);
    m_platforms.emplace_back(sf::Vector2f{800.0f, 420.0f}, sf::Vector2f{40.0f, 200.0f}, PlatformType::Wall);
    m_platforms.emplace_back(sf::Vector2f{1200.0f, 420.0f}, sf::Vector2f{40.0f, 200.0f}, PlatformType::Wall);
    m_platforms.emplace_back(sf::Vector2f{1600.0f, 420.0f}, sf::Vector2f{40.0f, 200.0f}, PlatformType::Wall);
    m_platforms.emplace_back(sf::Vector2f{2000.0f, 420.0f}, sf::Vector2f{40.0f, 200.0f}, PlatformType::Wall);

    // ---- Elevated platforms ----
    m_platforms.emplace_back(sf::Vector2f{350.0f, 420.0f}, sf::Vector2f{140.0f, 20.0f}, PlatformType::Floor);
    m_platforms.emplace_back(sf::Vector2f{750.0f, 420.0f}, sf::Vector2f{140.0f, 20.0f}, PlatformType::Floor);
    m_platforms.emplace_back(sf::Vector2f{1150.0f, 420.0f}, sf::Vector2f{140.0f, 20.0f}, PlatformType::Floor);
    m_platforms.emplace_back(sf::Vector2f{1000.0f, 300.0f}, sf::Vector2f{200.0f, 20.0f}, PlatformType::Floor);
    m_platforms.emplace_back(sf::Vector2f{600.0f, 320.0f}, sf::Vector2f{120.0f, 20.0f}, PlatformType::Floor);

    // ---- Boundary walls ----
    m_platforms.emplace_back(sf::Vector2f{-20.0f, 0.0f}, sf::Vector2f{20.0f, 800.0f}, PlatformType::Wall);
    m_platforms.emplace_back(sf::Vector2f{2500.0f, 0.0f}, sf::Vector2f{20.0f, 800.0f}, PlatformType::Wall);

    // ---- Enemies ----
    auto melee = std::make_unique<MeleeEnemy>();
    melee->setPosition({600.0f, 580.0f});
    melee->setSpawnPosition({600.0f, 580.0f});
    m_enemies.push_back(std::move(melee));

    auto ranged = std::make_unique<RangedEnemy>();
    ranged->setPosition({1400.0f, 580.0f});
    ranged->setSpawnPosition({1400.0f, 580.0f});
    m_enemies.push_back(std::move(ranged));

    auto tank = std::make_unique<TankEnemy>();
    tank->setPosition({1800.0f, 572.0f});
    tank->setSpawnPosition({1800.0f, 572.0f});
    m_enemies.push_back(std::move(tank));
}
