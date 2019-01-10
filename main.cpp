#include <SFML/Graphics.hpp>

int main() 
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Hello World");
    sf::Event e;
    while (window.isOpen()) {
        while(window.pollEvent(e)) {
            if (e.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color::White);
        window.display();
    }
    return 0;
}