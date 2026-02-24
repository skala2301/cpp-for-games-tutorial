#pragma once

#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

class Tree {
public:
    Tree(sf::Vector2f basePosition, float trunkHeight, float canopySize);

    void render(sf::RenderTarget& target) const;

private:
    sf::RectangleShape m_trunk;
    sf::ConvexShape    m_canopy;
};
