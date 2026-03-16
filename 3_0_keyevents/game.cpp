#include <SFML/Graphics.hpp>
#include <iostream>

void pullEvents(sf::RenderWindow& window, sf::Sprite& player);
void update(sf::RenderWindow& window, sf::Sprite& player, sf::RectangleShape& ground, float& deltaTime);
void render(sf::RenderWindow& window, sf::Sprite& player, sf::RectangleShape& ground);
namespace World{
    bool isFalling{false};
    float jumpVelocity{0};
    float gravity{9.8f};
    float velocityX{0.0f};
}

int main(){
    int x{192};
    int y{240};
    int frameWidth{240};
    int frameHeight{240};
    int xOffset{240};
    
    
    sf::RenderWindow window({800, 600}, "Pressed Shit");
    sf::Texture texture;
    sf::Sprite player;
    sf::IntRect playerRect{xOffset, 0, frameWidth, frameHeight};
    sf::RectangleShape ground{{800, 100}};

    if(!texture.loadFromFile("./character.png")){
        std::cerr<<"Error loading file.";
        return -1;
    }
    float windowWidth{(float)(window.getSize().x)};
    float windowHeight{(float)(window.getSize().y)};
    player.setTexture(texture);
    player.setOrigin((float)(frameWidth/2), (float)(frameHeight));
    player.setTextureRect(playerRect);
    ground.setPosition(0, windowHeight - ground.getSize().y);
    player.setPosition((float)(windowWidth/2), ground.getPosition().y);
    sf::Clock clock;
    float deltaTime{0.0f};
    float totalTime{0.0f};
    while(window.isOpen()){
        sf::Time elapsedTime{clock.restart()};
        deltaTime = elapsedTime.asSeconds();
        totalTime += elapsedTime.asSeconds();
        //std::cout<<"Time elapsed: "<<deltaTime<<std::endl;
        if(deltaTime >= 1.0f) {
        
            std::cout<<"Time elapsed: "<<totalTime<<std::endl;
        }
        pullEvents(window, player);
        update(window, player, ground, deltaTime);
        render(window, player, ground);
        
        if(totalTime >= 10.0f) totalTime = 0.0f;
    }


}



void pullEvents(sf::RenderWindow& window, sf::Sprite& player){
    sf::Event event;
    while(window.pollEvent(event)){
        if(event.type == sf::Event::Closed) window.close();
        if(event.type == sf::Event::KeyPressed){
            if(event.key.code == sf::Keyboard::Space){
                if(!World::isFalling){
                    World::jumpVelocity = 1000.0f;
                    World::isFalling = true;
                }
                
                std::cout<<"YVel: "<<World::jumpVelocity<<std::endl;
            }
        }
    }
};
void update(sf::RenderWindow& window, sf::Sprite& player, sf::RectangleShape& ground, float& deltaTime){
    float maxSpeed = 200.0f;
    float acceleration = 700.0f;
    float friction = 500.0f;

    float jumpV{-(World::jumpVelocity * deltaTime)};
    float g{(World::gravity)};
    
    if(World::isFalling){
        std::cout<<"falling at: "<<jumpV<<std::endl;
        std::cout<<"gravity: "<<g<<std::endl;
        World::jumpVelocity -= g;
    }
    
    float playerYPos{player.getPosition().y};
    float playerXPos{player.getPosition().x};
    float groundYPos{ground.getPosition().y};
    
    if(playerYPos >= groundYPos) {
        World::isFalling = false;
        World::jumpVelocity = 0;
        player.setPosition(playerXPos, groundYPos + 1.0f);
    }
    
    //std::cout<<"Pixels moved: "<<pixelsMoved<<std::endl;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        World::velocityX += acceleration * deltaTime;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        World::velocityX -= acceleration * deltaTime;
    }else {
        if (World::velocityX > 0) {
            World::velocityX -= friction * deltaTime;
            if (World::velocityX < 0) World::velocityX = 0; // don't overshoot
        } else if (World::velocityX < 0) {
            World::velocityX += friction * deltaTime;
            if (World::velocityX > 0) World::velocityX = 0; // don't overshoot
        }
    }
    
    if (World::velocityX > maxSpeed) World::velocityX = maxSpeed;
    if (World::velocityX < -maxSpeed) World::velocityX = -maxSpeed;
    player.move(World::velocityX * deltaTime, jumpV);
    if(deltaTime >= 1.0f) {
        deltaTime = 0.0f;
    }
};
void render(sf::RenderWindow& window, sf::Sprite& player, sf::RectangleShape& ground){
    window.clear(sf::Color::Red);
    window.draw(player);
    window.draw(ground);
    window.display();
};