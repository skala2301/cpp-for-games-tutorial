#include "Game.hpp"

#include <algorithm>
#include <cmath>
#include <string>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>

#include "Abilities/BulletAbility.hpp"
#include "Core/Constants.hpp"

Game::Game()
    : m_window(sf::VideoMode(constants::WINDOW_WIDTH, constants::WINDOW_HEIGHT),
               constants::WINDOW_TITLE,
               sf::Style::Close | sf::Style::Titlebar)
    , m_player(std::make_unique<Player>())
    , m_camera(sf::Vector2f{static_cast<float>(constants::WINDOW_WIDTH),
                            static_cast<float>(constants::WINDOW_HEIGHT)}) {
    m_window.setFramerateLimit(60);

    // Try to load a system font for HUD text (WSL + Linux + Windows paths)
    if (m_font.loadFromFile("/mnt/c/Windows/Fonts/arial.ttf")) {
        m_fontLoaded = true;
    } else if (m_font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) {
        m_fontLoaded = true;
    } else if (m_font.loadFromFile("/usr/share/fonts/TTF/DejaVuSans.ttf")) {
        m_fontLoaded = true;
    } else if (m_font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
        m_fontLoaded = true;
    }

    // Load first scene
    m_sceneManager.loadScene(0);
    loadCurrentScene();
}

void Game::run() {
    while (m_window.isOpen()) {
        const float dt = m_clock.restart().asSeconds();

        processEvents();

        if (m_gameState == GameState::Playing) {
            m_inputHandler.handleInput(*m_player);
            update(dt);
        }

        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (m_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            m_window.close();
        }

        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) {
                m_window.close();
            }

            // Restart on R key when game over or victory
            if ((m_gameState == GameState::GameOver || m_gameState == GameState::Victory) &&
                event.key.code == sf::Keyboard::R) {
                m_gameState = GameState::Playing;
                m_player = std::make_unique<Player>();
                m_projectiles.clear();
                m_sceneManager.loadScene(0);
                loadCurrentScene();
            }
        }
    }
}

void Game::update(float dt) {
    auto& scene = m_sceneManager.getCurrentScene();

    // AP recovery for player and enemies
    m_player->getStats().recoverAP(dt);
    for (auto& enemy : scene.getEnemies()) {
        if (enemy && enemy->isAlive()) {
            enemy->getStats().recoverAP(dt);
        }
    }

    // Update ability cooldowns
    m_player->updateAbilityCooldowns(dt);
    for (auto& enemy : scene.getEnemies()) {
        if (enemy && enemy->isAlive()) {
            enemy->updateAbilityCooldowns(dt);
        }
    }

    // AI update
    for (auto& enemy : scene.getEnemies()) {
        if (enemy && enemy->isAlive()) {
            enemy->update(dt);
        }
    }

    // Physics (fixed timestep internally)
    m_physicsEngine.update(dt, *m_player, scene.getEnemies(), scene.getPlatforms());

    // Platform collision resolution
    m_collisionSystem.resolveEntityPlatformCollisions(*m_player, scene.getPlatforms());
    for (auto& enemy : scene.getEnemies()) {
        if (enemy && enemy->isAlive()) {
            m_collisionSystem.resolveEntityPlatformCollisions(*enemy, scene.getPlatforms());
        }
    }

    // Combat collision
    m_collisionSystem.resolveCombatCollisions(*m_player, scene.getEnemies());

    // Check for bullet projectile spawn requests
    spawnProjectiles();

    // Update and resolve projectiles
    updateProjectiles(dt);
    resolveProjectileCollisions();

    // Player update
    m_player->update(dt);

    // Camera
    m_camera.update(m_player->getPosition(), m_player->isFacingRight(), dt);

    // Remove dead enemies
    auto& enemies = scene.getEnemies();
    enemies.erase(
        std::remove_if(enemies.begin(), enemies.end(),
            [](const auto& e) { return !e || !e->isAlive(); }),
        enemies.end());

    // Destroy entities that fell off
    if (m_player->getPosition().y > constants::KILL_PLANE_Y) {
        m_player->getStats().health = 0.0f;
    }
    enemies.erase(
        std::remove_if(enemies.begin(), enemies.end(),
            [](const auto& e) { return e && e->getPosition().y > constants::KILL_PLANE_Y; }),
        enemies.end());

    // Remove dead projectiles
    m_projectiles.erase(
        std::remove_if(m_projectiles.begin(), m_projectiles.end(),
            [](const auto& p) { return !p || !p->isAlive(); }),
        m_projectiles.end());

    // Check transitions
    checkSceneTransition();
    checkGameOver();
}

void Game::render() {
    m_window.clear(sf::Color(40, 40, 60));

    // Set camera view for game world
    m_window.setView(m_camera.getView());

    // Render scene (platforms, trees, enemies)
    m_sceneManager.getCurrentScene().render(m_window);

    // Render projectiles
    for (const auto& proj : m_projectiles) {
        if (proj && proj->isAlive()) {
            proj->render(m_window);
        }
    }

    // Render player
    if (m_player && m_player->isAlive()) {
        m_player->render(m_window);
    }

    // Reset to default view for HUD
    m_window.setView(m_window.getDefaultView());

    if (m_gameState == GameState::Playing) {
        renderHUD();
    } else if (m_gameState == GameState::GameOver) {
        renderGameOver();
    } else if (m_gameState == GameState::Victory) {
        renderVictory();
    }

    m_window.display();
}

void Game::renderHUD() {
    // Health bar background
    sf::RectangleShape healthBg({204.0f, 24.0f});
    healthBg.setPosition(10.0f, 10.0f);
    healthBg.setFillColor(sf::Color(60, 60, 60));
    healthBg.setOutlineColor(sf::Color::White);
    healthBg.setOutlineThickness(1.0f);
    m_window.draw(healthBg);

    // Health bar fill
    const float healthPct = m_player->getStats().health / m_player->getStats().maxHealth;
    sf::RectangleShape healthFill({200.0f * healthPct, 20.0f});
    healthFill.setPosition(12.0f, 12.0f);
    healthFill.setFillColor(healthPct > 0.3f ? sf::Color::Green : sf::Color::Red);
    m_window.draw(healthFill);

    // AP bar background
    sf::RectangleShape apBg({204.0f, 14.0f});
    apBg.setPosition(10.0f, 38.0f);
    apBg.setFillColor(sf::Color(60, 60, 60));
    apBg.setOutlineColor(sf::Color(180, 180, 180));
    apBg.setOutlineThickness(1.0f);
    m_window.draw(apBg);

    // AP bar fill
    const float apPct = m_player->getStats().actionPoints / m_player->getStats().maxActionPoints;
    sf::RectangleShape apFill({200.0f * apPct, 10.0f});
    apFill.setPosition(12.0f, 40.0f);
    apFill.setFillColor(sf::Color(80, 160, 255));
    m_window.draw(apFill);

    if (m_fontLoaded) {
        // Level text
        sf::Text levelText;
        levelText.setFont(m_font);
        levelText.setCharacterSize(18);
        levelText.setFillColor(sf::Color::White);
        levelText.setString("Level " + std::to_string(m_sceneManager.getCurrentIndex() + 1));
        levelText.setPosition(10.0f, 58.0f);
        m_window.draw(levelText);

        // HP numbers
        sf::Text hpText;
        hpText.setFont(m_font);
        hpText.setCharacterSize(14);
        hpText.setFillColor(sf::Color::White);
        hpText.setString(std::to_string(static_cast<int>(m_player->getStats().health)) + " / " +
                         std::to_string(static_cast<int>(m_player->getStats().maxHealth)));
        hpText.setPosition(220.0f, 12.0f);
        m_window.draw(hpText);

        // AP numbers
        sf::Text apText;
        apText.setFont(m_font);
        apText.setCharacterSize(11);
        apText.setFillColor(sf::Color(180, 210, 255));
        apText.setString("AP " + std::to_string(static_cast<int>(m_player->getStats().actionPoints)) +
                         " / " + std::to_string(static_cast<int>(m_player->getStats().maxActionPoints)));
        apText.setPosition(220.0f, 38.0f);
        m_window.draw(apText);

        // Active ability indicator
        sf::Text abilityText;
        abilityText.setFont(m_font);
        abilityText.setCharacterSize(16);
        abilityText.setFillColor(sf::Color::Yellow);
        const char* abilityNames[] = {"Melee", "Bullet"};
        std::size_t idx = m_player->getActiveAbilityIndex();
        std::string abilityName = (idx < 2) ? abilityNames[idx] : "???";
        abilityText.setString("[W] Ability: " + abilityName);
        abilityText.setPosition(10.0f, 82.0f);
        m_window.draw(abilityText);

        // Controls hint
        sf::Text controls;
        controls.setFont(m_font);
        controls.setCharacterSize(14);
        controls.setFillColor(sf::Color(180, 180, 180));
        controls.setString("Arrows:Move  S:Jump  A:Sprint  D:Attack  W:Switch  ESC:Quit");
        controls.setPosition(10.0f, static_cast<float>(constants::WINDOW_HEIGHT) - 25.0f);
        m_window.draw(controls);
    }
}

void Game::renderGameOver() {
    sf::RectangleShape overlay(sf::Vector2f{static_cast<float>(constants::WINDOW_WIDTH),
                                            static_cast<float>(constants::WINDOW_HEIGHT)});
    overlay.setFillColor(sf::Color(0, 0, 0, 150));
    m_window.draw(overlay);

    if (m_fontLoaded) {
        sf::Text gameOverText;
        gameOverText.setFont(m_font);
        gameOverText.setCharacterSize(60);
        gameOverText.setFillColor(sf::Color::Red);
        gameOverText.setString("GAME OVER");
        sf::FloatRect bounds = gameOverText.getLocalBounds();
        gameOverText.setPosition(
            (static_cast<float>(constants::WINDOW_WIDTH) - bounds.width) * 0.5f,
            (static_cast<float>(constants::WINDOW_HEIGHT) - bounds.height) * 0.5f - 40.0f);
        m_window.draw(gameOverText);

        sf::Text restartText;
        restartText.setFont(m_font);
        restartText.setCharacterSize(24);
        restartText.setFillColor(sf::Color::White);
        restartText.setString("Press R to restart");
        bounds = restartText.getLocalBounds();
        restartText.setPosition(
            (static_cast<float>(constants::WINDOW_WIDTH) - bounds.width) * 0.5f,
            (static_cast<float>(constants::WINDOW_HEIGHT) - bounds.height) * 0.5f + 40.0f);
        m_window.draw(restartText);
    }
}

void Game::renderVictory() {
    sf::RectangleShape overlay(sf::Vector2f{static_cast<float>(constants::WINDOW_WIDTH),
                                            static_cast<float>(constants::WINDOW_HEIGHT)});
    overlay.setFillColor(sf::Color(0, 0, 0, 150));
    m_window.draw(overlay);

    if (m_fontLoaded) {
        sf::Text victoryText;
        victoryText.setFont(m_font);
        victoryText.setCharacterSize(60);
        victoryText.setFillColor(sf::Color::Green);
        victoryText.setString("VICTORY!");
        sf::FloatRect bounds = victoryText.getLocalBounds();
        victoryText.setPosition(
            (static_cast<float>(constants::WINDOW_WIDTH) - bounds.width) * 0.5f,
            (static_cast<float>(constants::WINDOW_HEIGHT) - bounds.height) * 0.5f - 40.0f);
        m_window.draw(victoryText);

        sf::Text restartText;
        restartText.setFont(m_font);
        restartText.setCharacterSize(24);
        restartText.setFillColor(sf::Color::White);
        restartText.setString("Press R to play again");
        bounds = restartText.getLocalBounds();
        restartText.setPosition(
            (static_cast<float>(constants::WINDOW_WIDTH) - bounds.width) * 0.5f,
            (static_cast<float>(constants::WINDOW_HEIGHT) - bounds.height) * 0.5f + 40.0f);
        m_window.draw(restartText);
    }
}

void Game::checkSceneTransition() {
    const auto& exitZone = m_sceneManager.getCurrentScene().getExitZone();
    const sf::Vector2f pos = m_player->getPosition();

    if (pos.x >= exitZone.left && pos.x <= exitZone.left + exitZone.width &&
        pos.y >= exitZone.top && pos.y <= exitZone.top + exitZone.height) {
        if (m_sceneManager.hasNextScene()) {
            m_sceneManager.advanceToNextScene();
            loadCurrentScene();
        } else {
            m_gameState = GameState::Victory;
        }
    }
}

void Game::checkGameOver() {
    if (!m_player->isAlive()) {
        m_gameState = GameState::GameOver;
    }
}

void Game::loadCurrentScene() {
    auto& scene = m_sceneManager.getCurrentScene();
    m_player->setPosition(scene.getPlayerSpawn());
    m_player->setVelocity({0.0f, 0.0f});
    scene.setPlayerTarget(m_player.get());
    m_camera.setLevelBounds(scene.getLevelBounds());
    m_camera.snapTo(scene.getPlayerSpawn());
    m_projectiles.clear();
}

void Game::spawnProjectiles() {
    // Check player's abilities for BulletAbility spawn requests
    for (auto& ability : m_player->getAbilities()) {
        auto* bullet = dynamic_cast<BulletAbility*>(ability.get());
        if (bullet && bullet->shouldSpawnProjectile()) {
            m_projectiles.push_back(std::make_unique<Projectile>(
                bullet->getSpawnPosition(),
                bullet->getSpawnDirection(),
                constants::PROJECTILE_SPEED,
                constants::BULLET_BASE_DAMAGE * m_player->getStats().attack / 10.0f,
                constants::BULLET_IMPACT,
                constants::PROJECTILE_LIFETIME,
                constants::PROJECTILE_RADIUS));
            bullet->consumeSpawnRequest();
        }
    }
}

void Game::updateProjectiles(float dt) {
    for (auto& proj : m_projectiles) {
        if (proj && proj->isAlive()) {
            proj->update(dt);
        }
    }
}

void Game::resolveProjectileCollisions() {
    auto& enemies = m_sceneManager.getCurrentScene().getEnemies();

    for (auto& proj : m_projectiles) {
        if (!proj || !proj->isAlive()) continue;

        for (auto& enemy : enemies) {
            if (!enemy || !enemy->isAlive()) continue;

            // Circle-circle collision
            const float dx = proj->getPosition().x - enemy->getPosition().x;
            const float dy = proj->getPosition().y - enemy->getPosition().y;
            const float distSq = dx * dx + dy * dy;
            const float radSum = proj->getRadius() + enemy->getRadius();

            if (distSq <= radSum * radSum) {
                // Apply damage
                enemy->getStats().takeDamage(proj->getDamage());

                // Knockback
                const float dist = std::sqrt(distSq);
                const float dirX = (dist > 0.001f) ? dx / dist : proj->getDirection().x;
                sf::Vector2f vel = enemy->getVelocity();
                vel.x += proj->getImpact() * dirX;
                vel.y -= proj->getImpact() * 0.2f;
                enemy->setVelocity(vel);

                // Effects
                enemy->triggerFlash();
                enemy->showHealthBar();

                // Destroy projectile
                proj->kill();
                break;
            }
        }
    }
}
