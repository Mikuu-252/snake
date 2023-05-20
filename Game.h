#ifndef SNAKE_MW_SR17_272241_GAME_H
#define SNAKE_MW_SR17_272241_GAME_H

#include "Snake.h"
#include "Food.h"
#include <SFML/Graphics.hpp>

enum GameState {
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
    sf::Color foodColor;
};

struct Button {
    sf::RectangleShape rectangle;
    float sizeX;
    float sizeY;
    float borderSize;
    sf::Color fillColor;
    sf::Color borderColor;
};

class Game {
    int boardWidth;
    int boardHeight;
    Snake snake;
    Food food;
    int maxPoints;
    int points;
    GameState gameState;
    Field field;
    Button button;

public:
    Game(int width, int height);
    void gameController();

    void play();
    void drawGame(sf::RenderWindow &win);
    void inputsGame(sf::Event &event);
    void checkGameEnd();

    void menu();
    void drawMenu(sf::RenderWindow &win);

    bool foodCollision();
    bool boardCollision();
    bool snakeCollision();

    void generateFood();
};


#endif //SNAKE_MW_SR17_272241_GAME_H
