#pragma once

#include <cstdint>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "Physics/AABB.hpp"

enum class PlatformType : std::uint8_t {
    Floor,
    Wall
};

class Platform {
public:
    Platform(sf::Vector2f position, sf::Vector2f size, PlatformType type);

    void render(sf::RenderTarget& target) const;

    [[nodiscard]] const AABB& getAABB() const noexcept { return m_aabb; }
    [[nodiscard]] PlatformType getType() const noexcept { return m_type; }

private:
    sf::RectangleShape m_shape;
    AABB               m_aabb;
    PlatformType       m_type;
};
