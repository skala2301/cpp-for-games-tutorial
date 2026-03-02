#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Facing Direction");
    window.setFramerateLimit(60);
    
    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile("../assets/sprites/character.png")) {
        std::cerr << "Error loading player.png" << std::endl;
        return -1;
    }
    
    sf::Sprite player;
    player.setTexture(playerTexture);
    
    // Set origin to center
    player.setTextureRect({0,0,120,120});
    sf::FloatRect bounds = player.getLocalBounds();
    player.setOrigin(bounds.width / 2, bounds.height / 2);
    player.setPosition(400, 300);
    
    
    float speed = 200.0f;
    bool facingRight = true;  // Track facing direction
    
    sf::Clock clock;
    
    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                window.close();
        }
        
        // Movement with direction flipping
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            player.move(-speed * deltaTime, 0);
            if (facingRight) {
                player.setScale(-1, 1);  // Flip horizontally
                facingRight = false;
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            player.move(speed * deltaTime, 0);
            if (!facingRight) {
                player.setScale(1, 1);  // Face right (normal)
                facingRight = true;
            }
        }
        
        window.clear(sf::Color::Black);
        window.draw(player);
        window.display();
    }
    
    return 0;
}