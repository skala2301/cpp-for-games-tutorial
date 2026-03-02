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
        void move(const sf::Vector2f deltaV){
            this->sprite.move(deltaV);
        }
        sf::Vector2f getSpeed(){
            return this->walkSpeed;
        }
};


void eventHandler(sf::RenderWindow& window);
void update(sf::Time t, Player& player, sf::RenderWindow& window);
void render(Player& player, sf::RenderWindow& window);

int main(){
    sf::RenderWindow window({800, 600}, "");
    window.setFramerateLimit(60);
    sf::Texture spriteTexture;
    if(!spriteTexture.loadFromFile("../assets/sprites/character.png")){
        std::cerr<<"Texture could not be loaded."<<std::endl;
        return -1;
    }
    Player player{spriteTexture, {0,0,120,120}};
    player.setPosition({200,200});
    player.scale({2,2});
    sf::Clock clock;
    while (window.isOpen())
    {
        sf::Time t = clock.restart();
        eventHandler(window);
        update(t, player, window);
        render(player, window);
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
void update(sf::Time t, Player& player, sf::RenderWindow& window){
    sf::Vector2f movement{0, 0};
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) movement.x += player.getSpeed().x;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))  movement.x -= player.getSpeed().x;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))    movement.y -= player.getSpeed().y;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))  movement.y += player.getSpeed().y;
    
    // Normalize to fix diagonal speed
    float length = std::sqrt(movement.x * movement.x + movement.y * movement.y);
    if (length > 0) movement /= length;
    
    movement.x *= player.getSpeed().x;
    movement.y *= player.getSpeed().y;  
    player.move(movement * t.asSeconds());
};
void render(Player& player, sf::RenderWindow& window){
    window.clear(sf::Color::Black);
    window.draw(player.getSprite());
    window.display();
};