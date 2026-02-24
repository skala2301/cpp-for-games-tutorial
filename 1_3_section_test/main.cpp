#include <SFML/Graphics.hpp>

namespace constantValues{
    const double speed{200};
    sf::Int32 elapsedTime=0;
    sf::Color color(sf::Color::Black);
    constexpr int frames{60};
    constexpr double timeLimit{1000000};
    sf::VideoMode videoMode({640,480});
}


void update(sf::Time t);
void render(sf::RenderWindow& window);
void setColor(sf::Color);
void handleEvent(sf::RenderWindow& window);


int main(){
    sf::RenderWindow window(constantValues::videoMode,"Color Switcher");
    sf::Clock clock;
    window.setFramerateLimit(constantValues::frames);
    while(window.isOpen()){
        sf::Time elapsed = clock.restart();
        sf::Event event;
        handleEvent(window);
        update(elapsed);
        render(window);
    }
}


void handleEvent(sf::RenderWindow& window){
    sf::Event event;
    while(window.pollEvent(event)){
        if(event.type == sf::Event::Closed) window.close();
        if(event.type == sf::Event::KeyPressed){
            if(event.key.code == sf::Keyboard::Escape) window.close();
            if(event.key.code == sf::Keyboard::R) setColor(sf::Color::Red);
            if(event.key.code == sf::Keyboard::G) setColor(sf::Color::Green);
            if(event.key.code == sf::Keyboard::B) setColor(sf::Color::Blue);
        }
    }
}

void update(sf::Time t){
    constantValues::elapsedTime += t.asMilliseconds();
    if(constantValues::elapsedTime > constantValues::timeLimit){
        constantValues::elapsedTime = 0;
    }
}
void render(sf::RenderWindow& window){
    window.clear(constantValues::color);
    window.display();
}

void setColor(sf::Color color){
    constantValues::color=color;
}