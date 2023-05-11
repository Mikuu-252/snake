#include <iostream>
#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow win(sf::VideoMode(400, 200), "My Window");

    while (win.isOpen())
    {
        sf::Event event;
        while (win.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                win.close();
        }

        win.clear();
        win.display();
    }
    return 0;
}