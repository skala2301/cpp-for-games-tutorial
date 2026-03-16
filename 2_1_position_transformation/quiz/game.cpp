#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>


class Player{
    private:
        sf::Sprite sprite;
        sf::Vector2f walkSpeed{200,200};
    public:
        Player(sf::Texture& texture, const sf::IntRect rect){
            this->sprite.setTexture(texture);
            this->sprite.setTextureRect(rect);
        };
        const sf::Sprite& getSprite(){
            return sprite;
        }
        void setPosition(const sf::Vector2f position){
            this->sprite.setPosition(position);
        }
        void scale(const sf::Vector2f ratio){
            this->sprite.scale(ratio);
        }
        void setScale(const sf::Vector2f ratio){
            this->sprite.setScale(ratio);
        }
        void move(const sf::Vector2f deltaV){
            this->sprite.move(deltaV);
        }
        sf::Vector2f getSpeed(){
            return this->walkSpeed;
        }
        const sf::FloatRect getLocalBoundaries(){
            return this->sprite.getLocalBounds();
        }
        void setOrigin(float x, float y){
            this->sprite.setOrigin(x,y);
        }
};


void eventHandler(sf::RenderWindow& window);
void update(sf::Time t, Player& player, sf::Sprite& icon, sf::RenderWindow& window);
void render(Player& player, sf::Sprite& icon, sf::RenderWindow& window);

int main(){
    sf::RenderWindow window({800, 600}, "Transformation Demo");
    window.setFramerateLimit(60);
    sf::Texture spriteTexture;
    sf::Texture coinTexture;
    if(!spriteTexture.loadFromFile("sprite.png")){
        std::cerr<<"Sprite Texture could not be loaded."<<std::endl;
        return -1;
    }
    if(!coinTexture.loadFromFile("../assets/sprites/gems_db16.png")){
        std::cerr<<"Icon Texture could not be loaded."<<std::endl;
        return -1;
    }
    sf::Sprite icon{coinTexture, {0,32,32,32}};
    Player player{spriteTexture, {0,0,120,120}};
    sf::FloatRect playerBoundaries{player.getLocalBoundaries()};
    sf::FloatRect iconBoundaries{icon.getLocalBounds()};

    player.setOrigin(playerBoundaries.width/2, playerBoundaries.height);
    icon.setOrigin(iconBoundaries.width/2, iconBoundaries.height/2);

    player.setPosition({60,120});
    icon.setPosition(window.getSize().x/2,window.getSize().y/2);


    // Animation variables
    float rotationSpeed = 45.0f;  // degrees per second
    float pulseTime = 0.0f;
    //player.scale({2,2});

    sf::Clock clock;
    while (window.isOpen())
    {
        sf::Time t = clock.restart();
        eventHandler(window);
        // Rotate continuously
        icon.rotate(rotationSpeed * t.asSeconds());
        
        // Pulsing scale effect (1.0 to 1.2 and back)
        pulseTime += t.asSeconds();
        float scale = 2.0f + std::sin(pulseTime*M_PI);  // Oscillates
        icon.setScale(scale, scale);
        update(t, player, icon, window);
        render(player, icon, window);
    }
    
}


void eventHandler(sf::RenderWindow& window){
    sf::Event event;
    while(window.pollEvent(event)){
        if(event.type == sf::Event::Closed) window.close();
        if(event.type == sf::Event::KeyPressed){
            switch (event.key.code)
            {
            case sf::Keyboard::Escape:
                window.close();
                break;
            default:
                break;
            }
        }
    }
};
void update(sf::Time t, Player& player, sf::Sprite& icon, sf::RenderWindow& window){
    sf::Vector2f movement{0, 0};
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        movement.x += player.getSpeed().x;
        player.setScale({1,1});
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))  {
        movement.x -= player.getSpeed().x;
        player.setScale({-1,1});
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))    movement.y -= player.getSpeed().y;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))  movement.y += player.getSpeed().y;
    
    // Normalize to fix diagonal speed
    float length = std::sqrt(movement.x * movement.x + movement.y * movement.y);
    if (length > 0) movement /= length;
    
    movement.x *= player.getSpeed().x;
    movement.y *= player.getSpeed().y;  
    player.move(movement * t.asSeconds());
};
void render(Player& player, sf::Sprite& icon, sf::RenderWindow& window){
    window.clear(sf::Color::Black);
    window.draw(player.getSprite());
    window.draw(icon);
    window.display();
};