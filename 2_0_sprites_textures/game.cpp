#include <SFML/Graphics.hpp>
#include <iostream>

void handleEvents(sf::RenderWindow& window);
void update(sf::Time time, sf::Sprite& sprite, sf::RenderWindow& window);
void render(sf::Sprite& sprite,sf::RenderWindow& window);

namespace globals{
    float cumulativeTime{0};
    int spriteIndex{1};
}

int main(){
    sf::RenderWindow window({800,600}, "Sprite Practice");
    window.setFramerateLimit(60);
    sf::Texture characterTexture;
    if(!characterTexture.loadFromFile("./assets/sprites/character.png")){
        std::cerr << "Error: Could not load character.png" << std::endl;
        return -1;  // Exit with error code as required
    }
    sf::Sprite sprite;
    sprite.setTexture(characterTexture);
    sprite.setTextureRect({0,0,120,120});
    sprite.setPosition(200, 150);
    sf::Clock clock;
    while (window.isOpen())
    {
        sf::Time time = clock.restart();
        handleEvents(window);
        update(time, sprite, window);
        render(sprite, window);
    }
    

    return 0;
}


void handleEvents(sf::RenderWindow& window){
    sf::Event event;
    while (window.pollEvent(event))
    {
        if(event.type == sf::Event::Closed) window.close();
        if(event.type == sf::Event::KeyPressed){
            if(event.key.code == sf::Keyboard::Escape) window.close();
        }
    }
    
}

void update(sf::Time time, sf::Sprite& sprite, sf::RenderWindow& window){
    globals::cumulativeTime += time.asSeconds();
    if(globals::cumulativeTime >= 1){
        globals::cumulativeTime = 0;
        sf::Rect rect(sprite.getTextureRect().left + (globals::spriteIndex * 120) ,0,120,120);
        sprite.setTextureRect(rect);
        globals::spriteIndex+=1;
    }
    if(sprite.getTextureRect().left > (120 * 5)){
        sf::Rect rect(0 ,0,120,120);
        sprite.setTextureRect(rect);
        globals::spriteIndex=0;
    }
}

void render(sf::Sprite& sprite,sf::RenderWindow& window){
    window.clear(sf::Color::Black);
    window.draw(sprite);
    window.display();
}