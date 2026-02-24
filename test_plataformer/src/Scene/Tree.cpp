#include "Scene/Tree.hpp"

Tree::Tree(sf::Vector2f basePosition, float trunkHeight, float canopySize) {
    // Trunk: brown rectangle
    const float trunkWidth = trunkHeight * 0.25f;
    m_trunk.setSize({trunkWidth, trunkHeight});
    m_trunk.setFillColor(sf::Color(139, 90, 43));
    m_trunk.setPosition(basePosition.x - trunkWidth * 0.5f,
                        basePosition.y - trunkHeight);

    // Canopy: green triangle (3-point ConvexShape)
    m_canopy.setPointCount(3);
    m_canopy.setPoint(0, {canopySize * 0.5f, 0.0f});             // top center
    m_canopy.setPoint(1, {0.0f, canopySize});                     // bottom-left
    m_canopy.setPoint(2, {canopySize, canopySize});               // bottom-right
    m_canopy.setFillColor(sf::Color(34, 139, 34));
    m_canopy.setPosition(basePosition.x - canopySize * 0.5f,
                         basePosition.y - trunkHeight - canopySize);
}

void Tree::render(sf::RenderTarget& target) const {
    target.draw(m_trunk);
    target.draw(m_canopy);
}
