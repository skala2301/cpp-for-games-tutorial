#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Rotating Coin");
    window.setFramerateLimit(60);
    
    // Load texture
    sf::Texture coinTexture;
    if (!coinTexture.loadFromFile("../assets/sprites/gems_db16.png")) {
        std::cerr << "Error loading coin.png" << std::endl;
        return -1;
    }
    
    // Create sprite
    sf::Sprite coin;
    coin.setTexture(coinTexture);
    coin.setTextureRect({0,32,32,32});
    
    // Set origin to center for natural rotation
    sf::FloatRect bounds = coin.getLocalBounds();
    coin.setOrigin(bounds.width / 2, bounds.height / 2);
    
    // Position at center
    coin.setPosition(400, 300);
    
    // Animation variables
    float rotationSpeed = 90.0f;  // degrees per second
    float pulseTime = 0.0f;
    
    sf::Clock clock;
    
    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        
        // Events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) window.close();
        }
        
        // Rotate continuously
        coin.rotate(rotationSpeed * deltaTime);
        
        // Pulsing scale effect (1.0 to 1.2 and back)
        pulseTime += deltaTime;
        float scale = 1.0f + 0.2f * std::sin(pulseTime * 2.0f);  // Oscillates
        coin.setScale(scale, scale);
        
        // Render
        window.clear(sf::Color(50, 50, 100));  // Dark blue background
        window.draw(coin);
        window.display();
    }
    
    return 0;
}