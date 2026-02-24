#include "Scene/LevelOne.hpp"

#include <memory>

#include "Entities/MeleeEnemy.hpp"

void LevelOne::load() {
    m_platforms.clear();
    m_trees.clear();
    m_enemies.clear();

    // Level bounds
    m_levelBounds = {0.0f, 0.0f, 2500.0f, 720.0f};
    m_playerSpawn = {100.0f, 500.0f};
    m_exitZone    = {2350.0f, 400.0f, 150.0f, 220.0f};

    // ---- Ground ----
    // Main ground
    m_platforms.emplace_back(sf::Vector2f{0.0f, 620.0f}, sf::Vector2f{800.0f, 100.0f}, PlatformType::Floor);
    m_platforms.emplace_back(sf::Vector2f{900.0f, 620.0f}, sf::Vector2f{600.0f, 100.0f}, PlatformType::Floor);
    m_platforms.emplace_back(sf::Vector2f{1600.0f, 620.0f}, sf::Vector2f{900.0f, 100.0f}, PlatformType::Floor);

    // ---- Platforms (stepping stones) ----
    m_platforms.emplace_back(sf::Vector2f{300.0f, 500.0f}, sf::Vector2f{150.0f, 20.0f}, PlatformType::Floor);
    m_platforms.emplace_back(sf::Vector2f{550.0f, 420.0f}, sf::Vector2f{150.0f, 20.0f}, PlatformType::Floor);
    m_platforms.emplace_back(sf::Vector2f{800.0f, 500.0f}, sf::Vector2f{100.0f, 20.0f}, PlatformType::Floor);
    m_platforms.emplace_back(sf::Vector2f{1100.0f, 480.0f}, sf::Vector2f{180.0f, 20.0f}, PlatformType::Floor);
    m_platforms.emplace_back(sf::Vector2f{1400.0f, 520.0f}, sf::Vector2f{120.0f, 20.0f}, PlatformType::Floor);
    m_platforms.emplace_back(sf::Vector2f{1700.0f, 460.0f}, sf::Vector2f{200.0f, 20.0f}, PlatformType::Floor);

    // ---- Walls ----
    // Left boundary wall
    m_platforms.emplace_back(sf::Vector2f{-20.0f, 0.0f}, sf::Vector2f{20.0f, 720.0f}, PlatformType::Wall);

    // ---- Trees ----
    m_trees.emplace_back(sf::Vector2f{200.0f, 620.0f}, 80.0f, 60.0f);
    m_trees.emplace_back(sf::Vector2f{1800.0f, 620.0f}, 100.0f, 80.0f);

    // ---- Enemies ----
    auto enemy1 = std::make_unique<MeleeEnemy>();
    enemy1->setPosition({700.0f, 580.0f});
    enemy1->setSpawnPosition({700.0f, 580.0f});
    m_enemies.push_back(std::move(enemy1));

    auto enemy2 = std::make_unique<MeleeEnemy>();
    enemy2->setPosition({1300.0f, 580.0f});
    enemy2->setSpawnPosition({1300.0f, 580.0f});
    m_enemies.push_back(std::move(enemy2));
}
