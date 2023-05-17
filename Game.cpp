#include <SFML/Graphics.hpp>
#include <iostream>
#include <windows.h>
#include "Game.h"

Game::Game(int boardWidth, int boardHeight)
          : boardWidth(boardWidth), boardHeight(boardHeight),
            snake(boardWidth, boardHeight),
            food(boardWidth, boardHeight),
            maxPoints(boardWidth * boardHeight),
            points(3),
            gameState(gameState::RunningGame) {
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

}

void Game::play() {
    sf::RenderWindow win(sf::VideoMode(((boardWidth)*(field.borderSize+field.fieldSize)), ((boardHeight)*(field.borderSize+field.fieldSize))), "Snake");
    win.setFramerateLimit(snake.getSpeed());

    while (win.isOpen())
    {
        sf::Event event;
        while (win.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                win.close();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                snake.turn(Direction::Left);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                snake.turn(Direction::Right);
            }
        }

        //Debug!
        snake.debugDisplay();
        std::cout << food.getX();
        std::cout << food.getY();

        snake.move();

        if(foodCollision()) {
            generateFood();
            points++;
        }

        gameEnd();

        if (gameState == gameState::EndGame){
            std::cout << "koniec";
        }

        win.clear();
        draw(win);
        win.display();
    }
}

void Game::draw(sf::RenderWindow &win) {
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

bool Game::foodCollision() {
    if (snake.getSnakeHead().x == food.getX() && snake.getSnakeHead().y == food.getY()) {
        snake.grow();
        return true;
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

void Game::gameEnd() {
    if (points == maxPoints) {
        gameState = gameState::EndGame;
    }
}
