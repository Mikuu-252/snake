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

struct Scores {
    int easy[10]{0};
    int normal[10]{0};
    int hard[10]{0};
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
    int scoreWidth;
    int scoreHeight;

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

    Scores scores;


public:
    Game(int width, int height);
    void gameController();

    //Game
    void play();
    void drawGame(sf::RenderWindow &win);
    void inputsGame(sf::Event &event);
    void checkGameEnd();
    void generateFood();

    bool foodCollision();
    bool boardCollision();
    bool snakeCollision();

    //Menu
    void drawMenu(sf::RenderWindow &win);
    void inputMenu(sf::Event &event, sf::RenderWindow &win);
    void newGame(sf::RenderWindow &win);
    void changeDifficulty();

    //Score board
    void drawScoreBoard(sf::RenderWindow &win);
    void inputScoreBoard(sf::Event &event, sf::RenderWindow &win);
    void updateScores();
    void saveScores();
    void loadScores();


};


#endif //SNAKE_MW_SR17_272241_GAME_H
