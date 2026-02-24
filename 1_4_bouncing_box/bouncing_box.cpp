#include <SFML/Graphics.hpp>

namespace constantValues{
    sf::VideoMode videoMode{800,600};
    sf::Vector2i direction{1,1};
    const sf::Vector2f speed{150, 100};

    const int frame{60};
    const float timeLimit{1};
    float cumulativeTime{0};

}

class Player{
    private:
        sf::RectangleShape rectangle{{50,50}};
    public:
        Player(sf::Color color=sf::Color::Green){
            this->rectangle.setFillColor(color);
            this->rectangle.setPosition({375, 275});
        };
        const sf::RectangleShape& get(){
            return this->rectangle;
        }
        void setPosition(sf::Vector2f position){
            this->rectangle.setPosition(position);
        }
        const sf::Vector2f getPosition(){
            return this->rectangle.getPosition();
        }
};

void handleEvents(sf::RenderWindow& window);
void update(Player& player, sf::RenderWindow& window, sf::Time elapsed);
void render(Player& player, sf::RenderWindow& window);
void move(Player& player, sf::Vector2f speed, sf::Vector2i direction);
void evalLimit(Player& player, sf::RenderWindow& window);

int main(){
    sf::RenderWindow window(constantValues::videoMode, "Bouncing Square");
    Player player(sf::Color::Green);
    window.setFramerateLimit(constantValues::frame);
    sf::Clock clock;
    while (window.isOpen())
    {
        sf::Time elapsed = clock.restart();
        handleEvents(window);
        update(player, window, elapsed);
        render(player, window);
    }

}


void handleEvents(sf::RenderWindow& window){
    sf::Event event;
    while(window.pollEvent(event)){
        if(event.type == sf::Event::Closed) window.close();
    }
}

void update(Player& player, sf::RenderWindow& window, sf::Time t){
    float deltaTime = t.asSeconds();
    constantValues::cumulativeTime += deltaTime;
    sf::Vector2f speed = deltaTime * constantValues::speed;
    move(player , speed, constantValues::direction);
    evalLimit(player, window);
    if(constantValues::cumulativeTime > constantValues::timeLimit){
        constantValues::cumulativeTime=0;
    }
}

void render(Player& player, sf::RenderWindow& window){
    window.clear(sf::Color::Black);
    window.draw(player.get());
    window.display();
}

void move(Player& player, sf::Vector2f speed, sf::Vector2i direction){
    sf::Vector2f position{player.getPosition()};
    float x = position.x += (speed.x * direction.x);
    float y = position.y += (speed.y * direction.y);
    player.setPosition({x,y});
};

void evalLimit(Player& player, sf::RenderWindow& window){
    if(window.getSize().x <= player.getPosition().x + player.get().getSize().x){
        constantValues::direction.x=-1;
    }else if(player.getPosition().x <= 0){
        constantValues::direction.x=1;
    }

    if(window.getSize().y <= player.getPosition().y + player.get().getSize().y){
        constantValues::direction.y=-1;
    }else if(player.getPosition().y <= 0){
        constantValues::direction.y=1;
    }
}