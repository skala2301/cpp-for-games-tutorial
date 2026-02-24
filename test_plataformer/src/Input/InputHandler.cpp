#include "Input/InputHandler.hpp"

#include <SFML/Window/Keyboard.hpp>

void InputHandler::handleInput(Player& player) const {
    // Movement
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        player.moveLeft();
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        player.moveRight();
    } else {
        player.stopHorizontal();
    }

    // Sprint (A key)
    player.sprint(sf::Keyboard::isKeyPressed(sf::Keyboard::A));

    // Jump (S key)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        player.jump();
    } else {
        player.releaseJump();
    }

    // Attack (D key)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        player.attack();
    }

    // Switch ability (W key — press once to cycle)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        player.switchAbility();
    } else {
        player.releaseSwitchAbility();
    }
}
