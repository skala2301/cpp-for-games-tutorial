#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Sprite Animation");
    window.setFramerateLimit(60);
    
    // Load sprite sheet
    sf::Texture spriteSheet;
    if (!spriteSheet.loadFromFile("../assets/sprites/character1.png")) {
        std::cerr << "Error loading sprite sheet" << std::endl;
        return -1;
    }
    
    // Create sprite
    sf::Sprite character;
    character.setTexture(spriteSheet);
    
    // Animation properties
    int frameWidth = 192;
    int frameHeight = 240;
    int totalFrames = 8;  // 8 frames in walk cycle
    int currentFrame = 0;
    
    float frameTime = 0.15f;  // 0.1 seconds per frame (10 FPS animation)
    float elapsedTime = 0.0f;
    
    // Set initial frame
    character.setTextureRect(sf::IntRect(240, 0, frameWidth, frameHeight));
    character.setPosition(200, 200);
    
    sf::Clock clock;
    
    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        
        // Events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                window.close();
        }
        
        // Update animation
        elapsedTime += deltaTime;
        
        
        if (elapsedTime >= frameTime) {
            currentFrame++;
            if (currentFrame >= totalFrames) {
                currentFrame = 0;  // Loop back to first frame
            }
            elapsedTime = 0.0f;

            // Update texture rectangle to show new frame
            int left = 240 + (int)(currentFrame * frameWidth);
            character.setTextureRect(sf::IntRect(left, 0, frameWidth, frameHeight));

            

        }
        
        // Render
        window.clear(sf::Color::Black);
        window.draw(character);
        window.display();
    }
    
    return 0;
}