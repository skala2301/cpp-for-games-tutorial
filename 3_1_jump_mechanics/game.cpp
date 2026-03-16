#include <SFML/Graphics.hpp>
#include <iostream>



namespace World{
    const float maxSpeed{200.0f};
    const float acceleration{700.0f};
    const float friction{500.0f};
    float velocityX{0.0f};
    // In your namespace
    float jumpVelocity = 0.0f;
    float gravity = 980.0f;        // px per second squared
    float jumpForce = 600.0f;      // initial jump strength
    float jumpHoldTime = 0.0f;     // how long jump has been held
    const float maxJumpHold = 0.2f; // max seconds you can hold jump
    bool isGrounded = false;
    bool jumpHeld = false;
}

void pullEvents(sf::RenderWindow& window, sf::Sprite& player);
void update(sf::RenderWindow& window, sf::Sprite& player, sf::RectangleShape& ground, float& deltaTime);
void render(sf::RenderWindow& window, sf::Sprite& player, sf::RectangleShape& ground);


int main(){
    sf::RenderWindow window({800, 600}, "Jump Mechanism");

    window.setFramerateLimit(60);
    sf::Texture texture;
    sf::Sprite player;
    sf::RectangleShape ground{{(float)window.getSize().x, 200.0f}};
    int frameWidth{192};
    int frameHeight{240};
    int x{0};
    int y{0};
    sf::IntRect playerRect{frameHeight, y, frameWidth, frameHeight};

    if(!texture.loadFromFile("./character.png")){
        std::cerr<<"Error loading texture.";
        return -1;
    }

    ground.setPosition({0.0f, (float)(window.getSize().x - ground.getSize().y)});

    player.setTexture(texture);
    player.setTextureRect(playerRect);
    player.setOrigin((float)frameWidth/2, (float)frameHeight);
    player.setPosition((float)(ground.getPosition().x / 2), (float)(ground.getPosition().y - 1));

    sf::Clock clock;
    while(window.isOpen()){
        float deltaTime = clock.restart().asSeconds();
        pullEvents(window, player);
        update(window, player, ground, deltaTime);
        render(window, player, ground);
    }
    return 0;
}


void pullEvents(sf::RenderWindow& window, sf::Sprite& player){
    sf::Event event;
    while(window.pollEvent(event)){
        if(event.type == sf::Event::Closed) window.close();
        if(event.type == sf::Event::KeyPressed){
            if(event.key.code == sf::Keyboard::Space && World::isGrounded){
                World::jumpVelocity = -World::jumpForce;
                World::isGrounded = false;
                World::jumpHeld = true;
                World::jumpHoldTime = 0.0f;
            }
        }
        if(event.type == sf::Event::KeyReleased){
            if(event.key.code == sf::Keyboard::Space) {
                World::jumpHeld = false;
            }
        }
            
    }
}
void update(sf::RenderWindow& window, sf::Sprite& player, sf::RectangleShape& ground, float& deltaTime){
    float groundYPos{ground.getPosition().y};
    float playerXPos{player.getPosition().x};
    // Extra upward boost while holding jump
    if(World::jumpHeld && World::jumpHoldTime < World::maxJumpHold){
        World::jumpVelocity -= 200.0f * deltaTime; // extra lift
        World::jumpHoldTime += deltaTime;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        World::velocityX += World::acceleration * deltaTime;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        World::velocityX -= World::acceleration * deltaTime;
    }else {
        if (World::velocityX > 0) {
            World::velocityX -= World::friction * deltaTime;
            if (World::velocityX < 0) World::velocityX = 0; // don't overshoot
        } else if (World::velocityX < 0) {
            World::velocityX += World::friction * deltaTime;
            if (World::velocityX > 0) World::velocityX = 0; // don't overshoot
        }
    }
    
    if (World::velocityX > World::maxSpeed) World::velocityX = World::maxSpeed;
    if (World::velocityX < -World::maxSpeed) World::velocityX = -World::maxSpeed;
    // Gravity always pulls down
    World::jumpVelocity += World::gravity * deltaTime * (int)(!World::isGrounded);

    // Apply vertical movement
    player.move(World::velocityX * deltaTime, World::jumpVelocity * deltaTime);

    // Ground check
    if(player.getPosition().y >= groundYPos){
        World::isGrounded = true;
        World::jumpHeld = false;
        World::jumpVelocity = 0;
        player.setPosition(playerXPos, groundYPos - 1);
    }
}
void render(sf::RenderWindow& window, sf::Sprite& player, sf::RectangleShape& ground){
    window.clear(sf::Color::Magenta);
    window.draw(player);
    window.draw(ground);
    window.display();
}