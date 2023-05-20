#ifndef SNAKE_MW_SR17_272241_GAME_H
#define SNAKE_MW_SR17_272241_GAME_H

#include "Snake.h"
#include "Food.h"
#include <SFML/Graphics.hpp>

enum class GameState {
    Menu,
    RunningGame,
    EndGame
};

enum class GameDifficulty {
    Easy,
    Normal,
    Hard
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
    float scaleX;
    float scaleY;
    float buttonSpace;
    sf::Color fillColor;
    sf::Color borderColor;
};

class Game {
    int boardWidth;
    int boardHeight;
    int menuWidth;
    int menuHeight;

    Snake snake;
    Food food;
    int maxPoints;
    int points;
    GameState gameState;
    GameDifficulty gameDifficulty;

    Field field;
    Button button;
    sf::Font fontTitle;
    sf::Font fontMenu;
    sf::Text textTitle;
    sf::Text textMenu;
    sf::Color fontMenuColor;
    sf::Color fontTitleColor;


public:
    Game(int width, int height);
    void gameController();

    void play();
    void drawGame(sf::RenderWindow &win);
    void inputsGame(sf::Event &event);
    void checkGameEnd();

    void drawMenu(sf::RenderWindow &win);
    void inputMenu(sf::Event &event, sf::RenderWindow &win);
    void newGame(sf::RenderWindow &win);
    void changeDifficulty();

    bool foodCollision();
    bool boardCollision();
    bool snakeCollision();

    void generateFood();
};


#endif //SNAKE_MW_SR17_272241_GAME_H
