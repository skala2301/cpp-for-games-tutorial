#include "Scene/LevelTwo.hpp"

#include <memory>

#include "Entities/MeleeEnemy.hpp"
#include "Entities/RangedEnemy.hpp"

void LevelTwo::load() {
    m_platforms.clear();
    m_trees.clear();
    m_enemies.clear();

    // Level bounds - taller level for vertical challenge
    m_levelBounds = {0.0f, -500.0f, 1800.0f, 1220.0f};
    m_playerSpawn = {100.0f, 600.0f};
    m_exitZone    = {1600.0f, -400.0f, 200.0f, 150.0f};

    // ---- Ground ----
    m_platforms.emplace_back(sf::Vector2f{0.0f, 680.0f}, sf::Vector2f{600.0f, 40.0f}, PlatformType::Floor);
    m_platforms.emplace_back(sf::Vector2f{1200.0f, 680.0f}, sf::Vector2f{600.0f, 40.0f}, PlatformType::Floor);

    // ---- Vertical stepping platforms ----
    m_platforms.emplace_back(sf::Vector2f{100.0f, 560.0f}, sf::Vector2f{150.0f, 20.0f}, PlatformType::Floor);
    m_platforms.emplace_back(sf::Vector2f{350.0f, 440.0f}, sf::Vector2f{150.0f, 20.0f}, PlatformType::Floor);
    m_platforms.emplace_back(sf::Vector2f{600.0f, 350.0f}, sf::Vector2f{200.0f, 20.0f}, PlatformType::Floor);
    m_platforms.emplace_back(sf::Vector2f{400.0f, 240.0f}, sf::Vector2f{150.0f, 20.0f}, PlatformType::Floor);
    m_platforms.emplace_back(sf::Vector2f{700.0f, 140.0f}, sf::Vector2f{180.0f, 20.0f}, PlatformType::Floor);
    m_platforms.emplace_back(sf::Vector2f{950.0f, 50.0f}, sf::Vector2f{200.0f, 20.0f}, PlatformType::Floor);
    m_platforms.emplace_back(sf::Vector2f{1200.0f, -50.0f}, sf::Vector2f{180.0f, 20.0f}, PlatformType::Floor);
    m_platforms.emplace_back(sf::Vector2f{1450.0f, -150.0f}, sf::Vector2f{200.0f, 20.0f}, PlatformType::Floor);
    m_platforms.emplace_back(sf::Vector2f{1500.0f, -300.0f}, sf::Vector2f{250.0f, 20.0f}, PlatformType::Floor);

    // ---- Walls (cave sides) ----
    m_platforms.emplace_back(sf::Vector2f{-20.0f, -500.0f}, sf::Vector2f{20.0f, 1220.0f}, PlatformType::Wall);
    m_platforms.emplace_back(sf::Vector2f{1800.0f, -500.0f}, sf::Vector2f{20.0f, 1220.0f}, PlatformType::Wall);

    // ---- Tree (sparse vegetation) ----
    m_trees.emplace_back(sf::Vector2f{250.0f, 680.0f}, 70.0f, 55.0f);

    // ---- Enemies ----
    auto melee = std::make_unique<MeleeEnemy>();
    melee->setPosition({500.0f, 640.0f});
    melee->setSpawnPosition({500.0f, 640.0f});
    m_enemies.push_back(std::move(melee));

    auto ranged1 = std::make_unique<RangedEnemy>();
    ranged1->setPosition({700.0f, 310.0f});
    ranged1->setSpawnPosition({700.0f, 310.0f});
    m_enemies.push_back(std::move(ranged1));

    auto ranged2 = std::make_unique<RangedEnemy>();
    ranged2->setPosition({1000.0f, 10.0f});
    ranged2->setSpawnPosition({1000.0f, 10.0f});
    m_enemies.push_back(std::move(ranged2));
}
