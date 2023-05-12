#include <iostream>
#include "Snake.h"

Snake::Snake(int boardSize) : boardSize(boardSize), snakeHead({boardSize/2, boardSize/2}), direction(Direction::Up), speed(1), gameEnd(false){
    snakeSegments.push_back(snakeHead);
    snakeSegments.push_back({snakeHead.x, snakeHead.y + 1});
    snakeSegments.push_back({snakeHead.x, snakeHead.y + 2});
}

void Snake::debugDisplay() {
    for (int y = 0; y < boardSize; y++) {
        for (int x = 0; x < boardSize; x++) {
            bool isSegment = false;
            bool isSegmentHead = false;
            for(std::size_t i=0; i < snakeSegments.size(); i++) {
                if (snakeSegments[i].x == x && snakeSegments[i].y == y && i == 0) {
                    std::cout << "S";
                    isSegment = true;
                    isSegmentHead = true;
                } else if (snakeSegments[i].x == x && snakeSegments[i].y == y) {
                    std::cout << "s";
                    isSegment = true;
                }
            }
            if(!isSegment){
                std::cout << ".";
            } else if(isSegmentHead && !isSegment) {
                std::cout << "S";
            }
        }
        std::cout << "\n";
    }
}

void Snake::move() {
    if(direction == Direction::Up){
        SnakeSegment newHead{snakeSegments[0].x,snakeSegments[0].y-speed};
        snakeSegments.insert(snakeSegments.begin(),newHead);
        snakeSegments.pop_back();
    }
    if(direction == Direction::Down){
        SnakeSegment newHead{snakeSegments[0].x,snakeSegments[0].y+speed};
        snakeSegments.insert(snakeSegments.begin(),newHead);
        snakeSegments.pop_back();
    }
    if(direction == Direction::Left){
        SnakeSegment newHead{snakeSegments[0].x-speed,snakeSegments[0].y};
        snakeSegments.insert(snakeSegments.begin(),newHead);
        snakeSegments.pop_back();
    }
    if(direction == Direction::Right){
        SnakeSegment newHead{snakeSegments[0].x+speed,snakeSegments[0].y};
        snakeSegments.insert(snakeSegments.begin(),newHead);
        snakeSegments.pop_back();
    }
}

void Snake::setDirection(Direction newDirection) {
    direction = newDirection;
}

void Snake::turn(Direction turn) {

    if(direction == Direction::Up && turn == Direction::Left){
        setDirection(Direction::Left);
        return;
    }
    if(direction == Direction::Up && turn == Direction::Right){
        setDirection(Direction::Right);
        return;
    }

    if(direction == Direction::Right && turn == Direction::Left){
        setDirection(Direction::Up);
        return;
    }
    if(direction == Direction::Right && turn == Direction::Right){
        setDirection(Direction::Down);
        return;
    }

    if(direction == Direction::Down && turn == Direction::Left){
        setDirection(Direction::Right);
        return;
    }
    if(direction == Direction::Down && turn == Direction::Right){
        setDirection(Direction::Left);
        return;
    }

    if(direction == Direction::Left && turn == Direction::Left){
        setDirection(Direction::Down);
        return;
    }
    if(direction == Direction::Left && turn == Direction::Right){
        setDirection(Direction::Up);
        return;
    }

}

