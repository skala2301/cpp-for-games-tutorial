#include <SFML/Graphics.hpp>
#include <iostream>
#include "animation.cpp"

// Animation states
enum class AnimationState {
    IDLE,
    WALK
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Animation States");
    window.setFramerateLimit(60);
    
    // Load sprite sheet
    // Assume: Row 0 = Idle (4 frames), Row 1 = Walk (6 frames)
    sf::Texture spriteSheet;
    if (!spriteSheet.loadFromFile("../assets/sprites/character1.png")) {
        std::cerr << "Error loading sprite sheet" << std::endl;
        return -1;
    }
    
    sf::Sprite character;
    character.setTexture(spriteSheet);
    
    // Animation properties
    int frameWidth = 192;
    int frameHeight = 240;
    Animation idle(frameWidth, frameHeight, 8, 0, 0.1f, true);   // 4 frames, row 0, loops
    Animation walk(frameWidth, frameHeight, 8, 1, 0.1f, true);   // 6 frames, row 1, loops
    Animation jump(frameWidth, frameHeight, 8, 2, 0.15f, true); // 3 frames, row 2, doesn't loop
    Animation* currentAnimation = &idle;
    
    
    character.setOrigin(frameWidth/2, frameHeight);
    character.setPosition(300, 300);
    currentAnimation->apply(character);
    // Movement
    float speed = 200.0f;
    bool facingRight = true;
    
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
        
        // Input and state management
        bool isMoving = false;
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            currentAnimation=&idle;
            character.move(-speed * deltaTime, 0);
            isMoving = true;
            if (facingRight) {
                character.setScale(-1, 1);
                facingRight = false;
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            currentAnimation=&idle;
            character.move(speed * deltaTime, 0);
            isMoving = true;
            if (!facingRight) {
                character.setScale(1, 1);
                facingRight = true;
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            //character.move(speed * deltaTime, 0);
            isMoving = true;
            currentAnimation=&jump;
        }
        
        currentAnimation->update(deltaTime);
        currentAnimation->apply(character);
        // Render
        window.clear(sf::Color(135, 206, 235));  // Sky blue
        window.draw(character);
        window.display();
    }
    
    return 0;
}