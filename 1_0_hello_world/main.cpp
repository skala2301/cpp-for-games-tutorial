#include <SFML/Graphics.hpp>
#include <iostream>


int main() {
    std::cout << "SFML Version: " 
              << SFML_VERSION_MAJOR << "." 
              << SFML_VERSION_MINOR << "." 
              << SFML_VERSION_PATCH << std::endl;
    
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Test");
    
    window.setFramerateLimit(60);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if(event.type == sf::Event::KeyPressed){
                if(event.key.code == sf::Keyboard::Escape) window.close();
            }
        }
        
        window.clear(sf::Color::Blue);
        window.display();
    }
    
    return 0;
}