#include <SFML/Graphics.hpp>
#include <iostream>

sf::Int64 time_data=0;

class Player{
    public:
        sf::RectangleShape m_shape{{100,50}};
        Player(){
            this->m_shape.setFillColor(sf::Color::Red);
            this->m_shape.setPosition({0,275});
        }
        void setPosition(sf::Vector2f position){
            this->m_shape.setPosition(position);
        }
        sf::Vector2f getPosition(){
            return this->m_shape.getPosition();
        }
};
void handleEvents(sf::RenderWindow& window);
void update(Player& p, sf::RenderWindow& window, sf::Time elapsed);
void render(Player& p, sf::RenderWindow& window);

namespace timerData{
    
    static sf::Int64 fpsTimer;
    static int speed;
};





int main(){
    timerData::fpsTimer=0;
    timerData::speed=300;
    Player player;
    sf::RenderWindow window(sf::VideoMode(800, 600), "Delta Time Test");

    window.setFramerateLimit(60);

    sf::Clock clock;
    while(window.isOpen()){
        sf::Time elapsed = clock.restart();
        
        handleEvents(window);

        update(player, window, elapsed);

        render(player, window);

    }


    return 0;
}

void handleEvents(sf::RenderWindow& window){
    sf::Event event;
    while(window.pollEvent(event)){
        if(event.type == sf::Event::Closed) window.close();
        if(event.type == sf::Event::KeyPressed){
            if(event.key.code == sf::Keyboard::Escape) window.close();
            if(event.key.code == sf::Keyboard::D) std::cout<<timerData::fpsTimer<<std::endl;
        }
    }
}

void update(Player& p, sf::RenderWindow& window, sf::Time elapsed){
    float x = p.getPosition().x;
    float y = p.getPosition().y;
    x += elapsed.asSeconds() * timerData::speed;
    if(x > window.getSize().x){
        x=-100;
    }
    p.setPosition({x,y});
}

void render(Player& p, sf::RenderWindow& window){
    window.clear(sf::Color::Black);
    window.draw(p.m_shape);
    window.display();
}
