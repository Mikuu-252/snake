#ifndef SNAKE_MW_SR17_272241_GAME_H
#define SNAKE_MW_SR17_272241_GAME_H

#include "Snake.h"
#include <SFML/Graphics.hpp>

enum gameState {
    Menu,
    RunningGame,
    EndGame
};

struct Field {
    sf::RectangleShape rectangle;
    float fieldSize;
    float borderSize;
    sf::Color fieldColor;
    sf::Color borderColor;
    sf::Color snakeHeadColor;
    sf::Color snakeBodyColor;
};

class Game {
    int boardWidth;
    int boardHeight;
    Snake snake;
    int maxPoints;
    int points;
    gameState gameState;
    Field field;

public:
    Game(int width, int height);
    void play();
    void draw(sf::RenderWindow &win);
};


#endif //SNAKE_MW_SR17_272241_GAME_H
