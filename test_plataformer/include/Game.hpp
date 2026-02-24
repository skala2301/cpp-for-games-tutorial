#pragma once

#include <memory>
#include <vector>

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Clock.hpp>

#include "Core/Camera.hpp"
#include "Core/GameState.hpp"
#include "Entities/Player.hpp"
#include "Entities/Projectile.hpp"
#include "Input/InputHandler.hpp"
#include "Physics/CollisionSystem.hpp"
#include "Physics/PhysicsEngine.hpp"
#include "Scene/SceneManager.hpp"

class Game {
public:
    Game();

    void run();

private:
    void processEvents();
    void update(float dt);
    void render();
    void renderHUD();
    void renderGameOver();
    void renderVictory();

    void checkSceneTransition();
    void checkGameOver();
    void loadCurrentScene();

    void spawnProjectiles();
    void updateProjectiles(float dt);
    void resolveProjectileCollisions();

    sf::RenderWindow        m_window;
    sf::Clock               m_clock;
    sf::Font                m_font;
    bool                    m_fontLoaded = false;

    std::unique_ptr<Player> m_player;
    SceneManager            m_sceneManager;
    InputHandler            m_inputHandler;
    PhysicsEngine           m_physicsEngine;
    CollisionSystem         m_collisionSystem;
    Camera                  m_camera;

    std::vector<std::unique_ptr<Projectile>> m_projectiles;

    GameState               m_gameState = GameState::Playing;
};
