#include "Physics/AABB.hpp"

#include <algorithm>
#include <cmath>

bool AABB::intersects(const AABB& other) const noexcept {
    return left < other.right && right > other.left &&
           top < other.bottom && bottom > other.top;
}

sf::Vector2f AABB::getOverlap(const AABB& other) const noexcept {
    const float overlapX = std::min(right, other.right) - std::max(left, other.left);
    const float overlapY = std::min(bottom, other.bottom) - std::max(top, other.top);
    return {overlapX, overlapY};
}

bool AABB::containsPoint(sf::Vector2f point) const noexcept {
    return point.x >= left && point.x <= right &&
           point.y >= top && point.y <= bottom;
}

sf::Vector2f AABB::center() const noexcept {
    return {(left + right) * 0.5f, (top + bottom) * 0.5f};
}

AABB AABB::fromCircle(sf::Vector2f pos, float radius) noexcept {
    return {pos.x - radius, pos.y - radius, pos.x + radius, pos.y + radius};
}

AABB AABB::fromRect(sf::Vector2f pos, sf::Vector2f size) noexcept {
    return {pos.x, pos.y, pos.x + size.x, pos.y + size.y};
}
