#include <iostream>
#include <SFML/Graphics.hpp>
#include "Snake.h"


int main() {
/*    sf::RenderWindow win(sf::VideoMode(400, 200), "My Window");

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
    }*/

    Snake player(11);

    player.debugDisplay();

    while(true){

        std::cout << "\n";
        player.move();
        player.move();
        player.move();

        player.turn(Direction::Right);
        system("cls");
        player.debugDisplay();
    }

    return 0;
}