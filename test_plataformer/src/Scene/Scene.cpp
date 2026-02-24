#include "Scene/Scene.hpp"

#include "Entities/Player.hpp"

void Scene::render(sf::RenderTarget& target) const {
    // Draw platforms
    for (const auto& platform : m_platforms) {
        platform.render(target);
    }

    // Draw trees
    for (const auto& tree : m_trees) {
        tree.render(target);
    }

    // Draw enemies
    for (const auto& enemy : m_enemies) {
        if (enemy && enemy->isAlive()) {
            enemy->render(target);
        }
    }
}

void Scene::setPlayerTarget(const Player* player) {
    for (auto& enemy : m_enemies) {
        if (enemy) {
            enemy->setTarget(player);
        }
    }
}
