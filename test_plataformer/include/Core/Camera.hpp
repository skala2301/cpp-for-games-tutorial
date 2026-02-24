#pragma once

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Vector2.hpp>

class Camera {
public:
    explicit Camera(sf::Vector2f viewSize);

    void update(sf::Vector2f targetPosition, bool targetFacingRight, float dt);
    void setLevelBounds(sf::FloatRect bounds);
    void snapTo(sf::Vector2f position);

    [[nodiscard]] const sf::View& getView() const noexcept { return m_view; }

private:
    sf::View      m_view;
    sf::FloatRect m_levelBounds{0.0f, 0.0f, 0.0f, 0.0f};
    bool          m_hasBounds = false;
};
