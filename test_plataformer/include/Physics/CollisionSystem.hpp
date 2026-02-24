#pragma once

#include <memory>
#include <vector>

#include <SFML/System/Vector2.hpp>

class Entity;
class Player;
class Enemy;
class Platform;

class CollisionSystem {
public:
    void resolveEntityPlatformCollisions(Entity& entity,
                                         const std::vector<Platform>& platforms);

    void resolveCombatCollisions(Player& player,
                                 std::vector<std::unique_ptr<Enemy>>& enemies);

private:
    struct CollisionResult {
        bool  collided = false;
        sf::Vector2f penetration{0.0f, 0.0f};
        bool  isGroundContact = false;
    };

    [[nodiscard]] CollisionResult checkEntityVsPlatform(
        const Entity& entity, const Platform& platform) const;

    void applyAbilityDamage(Entity& attacker, Entity& target);
};
