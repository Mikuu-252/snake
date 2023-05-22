#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <sstream>

#include "Game.h"

Game::Game(int boardWidth, int boardHeight)
          : boardWidth(boardWidth), boardHeight(boardHeight),
            menuWidth(400), menuHeight(600),
            scoreWidth(400), scoreHeight(600),
            snake(boardWidth, boardHeight),
            food(boardWidth, boardHeight),
            maxPoints(boardWidth * boardHeight),
            points(3),
            gameState(GameState::Menu),
            gameDifficulty(GameDifficulty::Normal) {

    //Field
    field.borderSize = 5;
    field.fieldSize = 20;
    field.fieldColor = sf::Color::Black;
    field.borderColor = sf::Color::Black;
    field.snakeHeadColor = sf::Color::Yellow;
    field.snakeBodyColor = sf::Color::Green;
    field.foodColor = sf::Color::Red;
    field.rectangle = sf::RectangleShape(sf::Vector2f(field.fieldSize, field.fieldSize));
    field.rectangle.setFillColor(field.fieldColor);
    field.rectangle.setOutlineColor(field.borderColor);
    field.rectangle.setOutlineThickness(field.borderSize);

    //Button
    button.scaleX = boardWidth*(field.borderSize+field.fieldSize) / menuWidth;
    button.scaleY = boardHeight*(field.borderSize+field.fieldSize) / menuHeight;
    button.sizeX = 200;
    button.sizeY = 50;
    button.buttonSpace = 15;
    button.fillColor = sf::Color::White;
    button.borderColor = sf::Color::Green;
    button.rectangle.setSize(sf::Vector2f(button.sizeX * button.scaleX, button.sizeY  * button.scaleY));

    //Font
    if (!fontTitle.loadFromFile("SnakeFont.otf"))
    {
        std::cout << "Font title load error";
    }
    if (!fontMenu.loadFromFile("Righteous.ttf"))
    {
        std::cout << "Font menu load error";
    }

    //Title
    textTitle.setFont(fontTitle);
    fontTitleColor = sf::Color::Green;
    textTitle.setString("Snake");
    textTitle.setCharacterSize(160);
    textTitle.setFillColor(fontTitleColor);

    //Text menu
    fontMenuColor = sf::Color::Black;
    textMenu.setFont(fontMenu);
    textMenu.setCharacterSize(button.sizeY * 0.6);
    textMenu.setStyle(sf::Text::Bold);
    textMenu.setFillColor(fontMenuColor);
    button.rectangle.setFillColor(button.fillColor);
    button.rectangle.setOutlineColor(button.borderColor);

    //Load scores
    loadScores();

}

void Game::gameController() {
    sf::RenderWindow win(sf::VideoMode(((boardWidth)*(field.borderSize+field.fieldSize)), ((boardHeight)*(field.borderSize+field.fieldSize))), "Snake");
    win.setFramerateLimit(snake.getSpeed());

    while (win.isOpen())
    {
        sf::Event event;
        while (win.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                win.close();

            //Menu controls
            if (gameState == GameState::Menu) {
                inputMenu(event, win);
            }

            //Score board controls
            if (gameState == GameState::Menu) {
                inputScoreBoard(event, win);
            }

            //Game controls
            if (gameState == GameState::RunningGame) {
                inputsGame(event);
            }

        }


        //Game
        if (gameState == GameState::RunningGame) {
            play();
        }

        //Menu
        if (gameState == GameState::Menu) {
            win.setSize((sf::Vector2u(menuWidth, menuHeight)));
        }

        //Score board
        if (gameState == GameState::EndGame) {
            win.setSize((sf::Vector2u(scoreWidth, scoreHeight)));
        }


        win.clear();

        //Draw menu
        if (gameState == GameState::Menu){
            drawMenu(win);
        }

        //Draw game
        if (gameState == GameState::RunningGame){
            drawGame(win);
        }

        //Score board
        if (gameState == GameState::EndGame) {
            drawScoreBoard(win);
        }


        win.display();
    }

}


bool Game::foodCollision() {
    if (snake.getSnakeHead().x == food.getX() && snake.getSnakeHead().y == food.getY()) {
        return true;
    }
    return false;
}

bool Game::snakeCollision() {
    for(std::size_t i=1; i < snake.getSnakeSegments().size(); i++) {
        if (snake.getSnakeSegments()[i].x == snake.getSnakeHead().x && snake.getSnakeSegments()[i].y == snake.getSnakeHead().y) {
            return true;
        }
    }
    return false;
}

void Game::generateFood() {
    food = Food(boardWidth, boardHeight);
    for(std::size_t i=0; i < snake.getSnakeSegments().size(); i++) {
        if (food.getX() == snake.getSnakeSegments()[i].x && food.getY() == snake.getSnakeSegments()[i].y) {
            generateFood();
        }
    }
}

bool Game::boardCollision() {
    if (snake.getSnakeHead().x < 0 || snake.getSnakeHead().x > boardWidth ||
        snake.getSnakeHead().y < 0 || snake.getSnakeHead().y > boardHeight) {
        return true;
    }
    return false;
}

void Game::checkGameEnd() {
    if (points == maxPoints) {
        updateScores();
        saveScores();
        gameState = GameState::EndGame;
    } else if(boardCollision()) {
        updateScores();
        saveScores();
        gameState = GameState::EndGame;
    } else if(snakeCollision()) {
        updateScores();
        saveScores();
        gameState = GameState::EndGame;
    } else {
        gameState = GameState::RunningGame;
    }
}

void Game::play() {

    snake.move();

    checkGameEnd();

    //Collisions
    if(foodCollision()) {
        generateFood();
        snake.grow();
        points++;
    }

}

void Game::drawGame(sf::RenderWindow &win) {
    bool isSegmentHead = false;
    field.rectangle.setPosition(field.borderSize,field.borderSize);

    for (int y = 0; y < boardHeight; y++) {
        for (int x = 0; x < boardWidth; x++) {
            bool isFill = false;

            //Snake Draw
            for(std::size_t i=0; i < snake.getSnakeSegments().size(); i++) {
                if (snake.getSnakeHead().x == x && snake.getSnakeHead().y == y && !isSegmentHead) {
                    field.rectangle.setPosition((field.borderSize+field.fieldSize)*x, (field.borderSize+field.fieldSize)*y);
                    field.rectangle.setFillColor(field.snakeHeadColor);
                    win.draw(field.rectangle);
                    isFill = true;
                    isSegmentHead = true;
                } else if (snake.getSnakeSegments()[i].x == x && snake.getSnakeSegments()[i].y == y) {
                    field.rectangle.setPosition((field.borderSize+field.fieldSize)*x, (field.borderSize+field.fieldSize)*y);
                    field.rectangle.setFillColor(field.snakeBodyColor);
                    win.draw(field.rectangle);
                    isFill = true;
                }
            }

            //Food Draw
            if (x == food.getX() && y == food.getY()) {
                field.rectangle.setFillColor(field.foodColor);
                field.rectangle.setPosition((field.borderSize+field.fieldSize)*x, (field.borderSize+field.fieldSize)*y);
                win.draw(field.rectangle);
                isFill = true;
            }

            //Empty Draw
            if (!isFill){
                field.rectangle.setFillColor(field.fieldColor);
                field.rectangle.setPosition((field.borderSize+field.fieldSize)*x, (field.borderSize+field.fieldSize)*y);
                win.draw(field.rectangle);
            }
        }
    }
}


void Game::inputsGame(sf::Event &event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Left) {
            snake.turn(Direction::Left);
        }

        if (event.key.code == sf::Keyboard::Right) {
            snake.turn(Direction::Right);
        }
    }
}

void Game::drawMenu(sf::RenderWindow &win) {

    //Title
    textTitle.setPosition(((((menuWidth-button.sizeX) * button.scaleX)/2)), 20);

    win.draw(textTitle);

    //Text menu
    for (int i = 0; i < 3; i++) {
        button.rectangle.setPosition((((menuWidth-button.sizeX) * button.scaleX)/2),
                                     (((menuHeight-button.sizeY)/2 * button.scaleY)+(((button.buttonSpace + button.sizeY)*button.scaleY)*i)));

        textMenu.setPosition((((menuWidth+button.sizeX) * button.scaleX)/5),
                         ((((menuHeight-button.sizeY)/2 * button.scaleY)+(((button.buttonSpace + button.sizeY)*button.scaleY)*i)))+10);

        if(i == 0){
            textMenu.setString("NOWA GRA");
        } else if (i == 1) {
            if(gameDifficulty == GameDifficulty::Easy) {
                textMenu.setString("LATWY");
            } else if (gameDifficulty == GameDifficulty::Normal) {
                textMenu.setString("NORMALNY");
            } else {
                textMenu.setString("TRUDNY");
            }
        } else if (i == 2) {
            textMenu.setString("EKRAN WYNIKOW");
        }

        win.draw(button.rectangle);
        win.draw(textMenu);
    }

}

void Game::newGame(sf::RenderWindow &win) {
    win.setFramerateLimit(snake.getSpeed());
    snake = Snake(boardWidth, boardHeight);
    food = Food(boardWidth, boardHeight);
    points = 3;
    gameState = GameState::RunningGame;
    win.setSize(sf::Vector2u((boardWidth)*(field.borderSize+field.fieldSize), (boardHeight)*(field.borderSize+field.fieldSize)));


}

void Game::inputMenu(sf::Event &event, sf::RenderWindow &win) {
    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            if(event.mouseButton.x > (menuWidth-button.sizeX)/2 && event.mouseButton.x < (menuWidth+button.sizeX)/2) {
                if(event.mouseButton.y > (menuHeight-button.sizeY)/2 && event.mouseButton.y < (menuHeight+button.sizeY)/2) {
                    newGame(win);
                }

                if(event.mouseButton.y > (button.buttonSpace + button.sizeY)+((menuHeight-button.sizeY)/2) && event.mouseButton.y < (button.buttonSpace + button.sizeY)+((menuHeight+button.sizeY)/2)) {
                    changeDifficulty();
                }

                if(event.mouseButton.y > 2*(button.buttonSpace + button.sizeY)+((menuHeight-button.sizeY)/2) && event.mouseButton.y < 2*(button.buttonSpace + button.sizeY)+((menuHeight+button.sizeY)/2)) {
                    gameState = GameState::EndGame;
                }
            }

        }
    }
}

void Game::changeDifficulty() {
    if(gameDifficulty == GameDifficulty::Easy) {
        gameDifficulty = GameDifficulty::Normal;
        snake.setSpeed(6);
    } else if (gameDifficulty == GameDifficulty::Normal) {
        gameDifficulty = GameDifficulty::Hard;
        snake.setSpeed(8);

    } else {
        gameDifficulty = GameDifficulty::Easy;
        snake.setSpeed(4);
    }
}

void Game::drawScoreBoard(sf::RenderWindow &win) {



    //Buttons
    for (int i = 0; i < 2; i++) {
        button.rectangle.setPosition((((i*button.sizeX) * button.scaleX)),
                                     (((menuHeight-button.sizeY) * button.scaleY))+10);

        textMenu.setPosition((((i*button.sizeX) * button.scaleX)+80),
                             (((menuHeight-button.sizeY) * button.scaleY))+10);

        if(i == 0){
            textMenu.setString("WRÓC");
        } else {
            if(gameDifficulty == GameDifficulty::Easy) {
                textMenu.setString("LATWY");
            } else if (gameDifficulty == GameDifficulty::Normal) {
                textMenu.setString("NORMALNY");
            } else {
                textMenu.setString("TRUDNY");
            }
        }

        win.draw(button.rectangle);
        win.draw(textMenu);
    }
}

void Game::inputScoreBoard(sf::Event &event, sf::RenderWindow &win) {

}

void Game::updateScores() {
    if (gameDifficulty == GameDifficulty::Easy) {
        if (points > scores.easy[9]) {
            scores.easy[9] = points;
            std::sort(scores.easy, scores.easy + 10, std::greater<int>());
        }
    } else if (gameDifficulty == GameDifficulty::Normal) {
        if (points > scores.normal[9]) {
            scores.normal[9] = points;
            std::sort(scores.normal, scores.normal + 10, std::greater<int>());
        }
    } else {
        if (points > scores.hard[9]) {
            scores.hard[9] = points;
            std::sort(scores.hard, scores.hard + 10, std::greater<int>());
        }
    }
}


void Game::saveScores() {
    std::ofstream file("scores.txt");
    if(file) {
        for (int i = 0; i < 10; ++i) {
            file << scores.easy[i] << "\n";
        }
        for (int i = 0; i < 10; ++i) {
            file << scores.normal[i] << "\n";
        }
        for (int i = 0; i < 10; ++i) {
            file << scores.hard[i] << "\n";
        }
    }
    file.close();
}

void Game::loadScores() {
    std::ifstream file("scores.txt");
    std::string line;

    for (int i = 0; i < 10; ++i) {
        std::getline(file, line);
        std::istringstream issline(line);
        issline >> scores.easy[i];
    }

    for (int i = 0; i < 10; ++i) {
        std::getline(file, line);
        std::istringstream issline(line);
        issline >> scores.normal[i];
    }

    for (int i = 0; i < 10; ++i) {
        std::getline(file, line);
        std::istringstream issline(line);
        issline >> scores.hard[i];
    }
}
