#pragma once

#include <SFML/System/Vector2.hpp>

struct AABB {
    float left   = 0.0f;
    float top    = 0.0f;
    float right  = 0.0f;
    float bottom = 0.0f;

    [[nodiscard]] bool intersects(const AABB& other) const noexcept;
    [[nodiscard]] sf::Vector2f getOverlap(const AABB& other) const noexcept;
    [[nodiscard]] bool containsPoint(sf::Vector2f point) const noexcept;
    [[nodiscard]] float width() const noexcept  { return right - left; }
    [[nodiscard]] float height() const noexcept { return bottom - top; }
    [[nodiscard]] sf::Vector2f center() const noexcept;

    static AABB fromCircle(sf::Vector2f pos, float radius) noexcept;
    static AABB fromRect(sf::Vector2f pos, sf::Vector2f size) noexcept;
};
