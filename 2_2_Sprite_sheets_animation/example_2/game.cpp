#include <SFML/Graphics.hpp>
#include <iostream>

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
    character.setOrigin(frameWidth/2, frameHeight);
    character.setPosition(300, 300);
    
    
    AnimationState currentState = AnimationState::IDLE;
    int currentFrame = 0;
    float elapsedTime = 0.0f;
    float frameTime = 0.1f;
    
    // State properties
    int idleFrames = 8;
    int walkFrames = 8;
    int idleRow = 0;
    int walkRow = 1;

    character.setTextureRect(sf::IntRect(240, idleRow * frameHeight, frameWidth, frameHeight));
    
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
            character.move(-speed * deltaTime, 0);
            isMoving = true;
            if (facingRight) {
                character.setScale(-1, 1);
                facingRight = false;
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            character.move(speed * deltaTime, 0);
            isMoving = true;
            if (!facingRight) {
                character.setScale(1, 1);
                facingRight = true;
            }
        }
        
        // State switching
        AnimationState newState = isMoving ? AnimationState::WALK : AnimationState::IDLE;
        if (newState != currentState) {
            currentState = newState;
            currentFrame = 0;  // Reset animation
            elapsedTime = 0.0f;
        }
        
        // Determine animation parameters based on state
        int totalFrames;
        int row;
        if (currentState == AnimationState::IDLE) {
            totalFrames = idleFrames;
            row = idleRow;
        } else {
            totalFrames = walkFrames;
            row = walkRow;
        }
        
        // Update animation
        elapsedTime += deltaTime;
        if (elapsedTime >= frameTime) {
            currentFrame++;
            if (currentFrame >= totalFrames) {
                currentFrame = 0;
            }
            elapsedTime = 0.0f;
            
            // Calculate texture rectangle
            int left = 240 + (currentFrame * frameWidth);
            int top = row * frameHeight;
            character.setTextureRect(sf::IntRect(left, top, frameWidth, frameHeight));
        }
        
        // Render
        window.clear(sf::Color(135, 206, 235));  // Sky blue
        window.draw(character);
        window.display();
    }
    
    return 0;
}