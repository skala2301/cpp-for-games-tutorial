#include <SFML/Graphics.hpp>
#include <iostream>

int main(){

    sf::RenderWindow window(sf::VideoMode({800,600}),"Two Sprites");
    sf::Texture spriteTexture;
    int frameWidth{64};
    int frameHeight{64};

    if(!spriteTexture.loadFromFile("./enemy.png")){
        std::cerr<<"Couldn´t load Texture.";
        return -1;
    }
    sf::Sprite enemy1;
    sf::Sprite enemy2;
    sf::IntRect enemy1Boundaries{0,0,frameWidth, frameHeight};
    sf::IntRect enemy2Boundaries{0,0,frameWidth, frameHeight};

    enemy1.setTexture(spriteTexture);
    enemy1.setOrigin({frameWidth/2, frameHeight/2});
    enemy1.setTextureRect(enemy1Boundaries);
    enemy1.setPosition({100,200});

    enemy2.setTexture(spriteTexture);
    enemy2.setOrigin({frameWidth/2, frameHeight/2});
    enemy2.setTextureRect(enemy2Boundaries);
    enemy2.setScale(-1,1);
    enemy2.setPosition({500,200});

    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed) window.close();
        }
        window.clear();
        window.draw(enemy1);
        window.draw(enemy2);
        window.display();
    }

    return 0;
}
