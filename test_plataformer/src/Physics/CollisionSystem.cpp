#include "Physics/CollisionSystem.hpp"

#include <cmath>

#include "Core/Constants.hpp"
#include "Entities/Enemy.hpp"
#include "Entities/Entity.hpp"
#include "Entities/Player.hpp"
#include "Scene/Platform.hpp"

void CollisionSystem::resolveEntityPlatformCollisions(
    Entity& entity,
    const std::vector<Platform>& platforms) {

    bool grounded = false;

    for (const auto& platform : platforms) {
        auto result = checkEntityVsPlatform(entity, platform);
        if (!result.collided) continue;

        sf::Vector2f pos = entity.getPosition();
        sf::Vector2f vel = entity.getVelocity();

        // Apply penetration resolution (checkEntityVsPlatform already chose the axis)
        pos -= result.penetration;

        if (result.isGroundContact) {
            grounded = true;
            vel.y = 0.0f;
        } else if (std::abs(result.penetration.y) > 0.0f) {
            // Hit ceiling
            if (vel.y < 0.0f) vel.y = 0.0f;
        }

        if (std::abs(result.penetration.x) > 0.0f) {
            vel.x = 0.0f;
        }

        entity.setPosition(pos);
        entity.setVelocity(vel);
    }

    entity.setOnGround(grounded);
}

void CollisionSystem::resolveCombatCollisions(
    Player& player,
    std::vector<std::unique_ptr<Enemy>>& enemies) {

    // Player abilities vs enemies
    for (auto& ability : player.getAbilities()) {
        if (!ability->isActive()) continue;

        for (auto& enemy : enemies) {
            if (!enemy || !enemy->isAlive()) continue;
            if (ability->hasHitEntity(enemy.get())) continue;

            if (ability->overlapsCircle(enemy->getPosition(), enemy->getRadius())) {
                ability->markEntityHit(enemy.get());
                const float rawDamage = ability->getBaseDamage() * player.getStats().attack / 10.0f;
                enemy->getStats().takeDamage(rawDamage);

                // Knockback
                const float dir = (enemy->getPosition().x >= player.getPosition().x) ? 1.0f : -1.0f;
                sf::Vector2f vel = enemy->getVelocity();
                vel.x += ability->getAttackImpact() * dir;
                vel.y -= ability->getAttackImpact() * 0.3f;
                enemy->setVelocity(vel);

                // Flash + health bar
                enemy->triggerFlash();
                enemy->showHealthBar();
            }
        }
    }

    // Enemy abilities vs player
    if (!player.isAlive()) return;

    for (auto& enemy : enemies) {
        if (!enemy || !enemy->isAlive()) continue;

        for (auto& ability : enemy->getAbilities()) {
            if (!ability->isActive()) continue;
            if (ability->hasHitEntity(&player)) continue;

            if (ability->overlapsCircle(player.getPosition(), player.getRadius())) {
                ability->markEntityHit(&player);
                const float rawDamage = ability->getBaseDamage() * enemy->getStats().attack / 10.0f;
                player.getStats().takeDamage(rawDamage);

                // Knockback
                const float dir = (player.getPosition().x >= enemy->getPosition().x) ? 1.0f : -1.0f;
                sf::Vector2f vel = player.getVelocity();
                vel.x += ability->getAttackImpact() * dir;
                vel.y -= ability->getAttackImpact() * 0.3f;
                player.setVelocity(vel);

                // Flash
                player.triggerFlash();
            }
        }
    }
}

CollisionSystem::CollisionResult CollisionSystem::checkEntityVsPlatform(
    const Entity& entity, const Platform& platform) const {

    CollisionResult result;

    const AABB entityBox = AABB::fromCircle(entity.getPosition(), entity.getRadius());
    const AABB& platBox = platform.getAABB();

    if (!entityBox.intersects(platBox)) return result;

    result.collided = true;

    const sf::Vector2f overlap = entityBox.getOverlap(platBox);

    // Determine penetration direction
    const sf::Vector2f entityCenter = entityBox.center();
    const sf::Vector2f platCenter = platBox.center();

    const float dx = entityCenter.x - platCenter.x;
    const float dy = entityCenter.y - platCenter.y;

    if (overlap.y <= overlap.x) {
        // Vertical resolution
        result.penetration.y = (dy > 0.0f) ? -overlap.y : overlap.y;
        result.isGroundContact = (dy < 0.0f);
    } else {
        // Horizontal resolution
        result.penetration.x = (dx > 0.0f) ? -overlap.x : overlap.x;
    }

    return result;
}

void CollisionSystem::applyAbilityDamage(Entity& attacker, Entity& target) {
    if (attacker.getAbilities().empty()) return;

    const auto& ability = attacker.getAbilities()[0];
    const float rawDamage = ability->getBaseDamage() * attacker.getStats().attack / 10.0f;
    target.getStats().takeDamage(rawDamage);
}
