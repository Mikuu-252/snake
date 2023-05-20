#include <iostream>
#include "Snake.h"

Snake::Snake(int boardWidth, int boardHeight)
            : boardWidth(boardWidth), boardHeight(boardHeight),
              snakeHead({boardWidth/2, boardHeight/2}),
              direction(Direction::Up),
              speed(6) {

    snakeSegments.push_back(snakeHead);
    snakeSegments.push_back({snakeHead.x, snakeHead.y + 1});
    snakeSegments.push_back({snakeHead.x, snakeHead.y + 2});
}

void Snake::debugDisplay() {
    bool isSegmentHead = false;
    for (int y = 0; y < boardHeight; y++) {
        for (int x = 0; x < boardWidth; x++) {
            bool isSegment = false;
            for(std::size_t i=0; i < snakeSegments.size(); i++) {
                if (snakeHead.x == x && snakeHead.y == y && !isSegmentHead) {
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
            }
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

void Snake::move() {
    if(direction == Direction::Up){
        SnakeSegment newHead{snakeHead.x,snakeHead.y-1};
        snakeHead = newHead;
        snakeSegments.insert(snakeSegments.begin(),newHead);
        snakeSegments.pop_back();
    }
    if(direction == Direction::Down){
        SnakeSegment newHead{snakeHead.x,snakeHead.y+1};
        snakeHead = newHead;
        snakeSegments.insert(snakeSegments.begin(),newHead);
        snakeSegments.pop_back();
    }
    if(direction == Direction::Left){
        SnakeSegment newHead{snakeHead.x-1,snakeHead.y};
        snakeHead = newHead;
        snakeSegments.insert(snakeSegments.begin(),newHead);
        snakeSegments.pop_back();
    }
    if(direction == Direction::Right){
        SnakeSegment newHead{snakeHead.x+1,snakeHead.y};
        snakeHead = newHead;
        snakeSegments.insert(snakeSegments.begin(),newHead);
        snakeSegments.pop_back();
    }
}

void Snake::setDirection(Direction newDirection) {
    direction = newDirection;
}

void Snake::turn(Direction turn) {
    if (turn == Direction::Left) {
        // Turn Left
        if (direction == Direction::Up) {
            setDirection(Direction::Left);
        } else if (direction == Direction::Right) {
            setDirection(Direction::Up);
        } else if (direction == Direction::Down) {
            setDirection(Direction::Right);
        } else if (direction == Direction::Left) {
            setDirection(Direction::Down);
        }
    } else if (turn == Direction::Right) {
        // Turn Right
        if (direction == Direction::Up) {
            setDirection(Direction::Right);
        } else if (direction == Direction::Right) {
            setDirection(Direction::Down);
        } else if (direction == Direction::Down) {
            setDirection(Direction::Left);
        } else if (direction == Direction::Left) {
            setDirection(Direction::Up);
        }
    }
}

void Snake::grow() {
    if(direction == Direction::Up){
        SnakeSegment newHead{snakeHead.x,snakeHead.y};
        snakeHead = newHead;
        snakeSegments.insert(snakeSegments.begin(),newHead);
    }
    if(direction == Direction::Down){
        SnakeSegment newHead{snakeHead.x,snakeHead.y};
        snakeHead = newHead;
        snakeSegments.insert(snakeSegments.begin(),newHead);
    }
    if(direction == Direction::Left){
        SnakeSegment newHead{snakeHead.x,snakeHead.y};
        snakeHead = newHead;
        snakeSegments.insert(snakeSegments.begin(),newHead);
    }
    if(direction == Direction::Right){
        SnakeSegment newHead{snakeHead.x,snakeHead.y};
        snakeHead = newHead;
        snakeSegments.insert(snakeSegments.begin(),newHead);
    }
}

const std::vector<SnakeSegment> &Snake::getSnakeSegments() const {
    return snakeSegments;
}

const SnakeSegment &Snake::getSnakeHead() const {
    return snakeHead;
}

int Snake::getSpeed() const {
    return speed;
}

void Snake::setSpeed(int speed) {
    Snake::speed = speed;
}

