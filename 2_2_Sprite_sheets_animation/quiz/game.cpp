#include <SFML/Graphics.hpp>
#include <iostream>


void pollEvents(sf::RenderWindow& window);
void update(sf::RenderWindow& window, sf::Sprite& character, float& elapsedTime);
void render(sf::RenderWindow& window, sf::Sprite& character);

int main(){

    sf::RenderWindow window(sf::VideoMode({800, 600}), "Animation Test");

    sf::Texture texture;

    int frameWidth{64};
    int frameHeight{64};

    if(!texture.loadFromFile("./character.png")) {
        std::cerr<<"Error loading file."<<std::endl;
        return -1;
    }

    sf::Sprite character;
    character.setTexture(texture);
    character.setTextureRect({0,0,frameWidth,frameHeight});
    character.setOrigin({(float)(frameWidth/2), (float)(frameHeight/2)});
    character.setPosition((float)(window.getSize().x/2), (float)(window.getSize().y/2));
    sf::Clock clock;
    float elapsedTime{0.0f};
    while(window.isOpen()){
        sf::Time t = clock.restart();
        elapsedTime += t.asSeconds();
        pollEvents(window);
        update(window, character, elapsedTime);
        render(window, character);
        
    }


    return 0;
}


void pollEvents(sf::RenderWindow& window){
    sf::Event event;
    while(window.pollEvent(event)){
        if(event.type == sf::Event::Closed) window.close();
    }
};
void update(sf::RenderWindow& window, sf::Sprite& character, float& elapsedTime){
    float frameTime = 0.1f;
    if(elapsedTime >= 1.00f){
        elapsedTime=0.00f;
    }
    if(elapsedTime >= frameTime){
        int maxFrames = 6;
        int w = character.getTextureRect().width;
        int h = character.getTextureRect().height;
        int l = character.getTextureRect().left;
        int x = l + w;
        if(x < w * maxFrames){
            character.setTextureRect({x,0,w,h});
        }else character.setTextureRect({0,0,w,h});
        elapsedTime -= frameTime;
        
    }
};
void render(sf::RenderWindow& window, sf::Sprite& character){
    window.clear(sf::Color::Cyan);
    window.draw(character);
    window.display();
};