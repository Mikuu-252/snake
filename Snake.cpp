#include <iostream>
#include "Snake.h"

Snake::Snake(int boardWidth, int boardHeight)
            : boardWidth(boardWidth), boardHeight(boardHeight),
              snakeHead({boardWidth/2, boardHeight/2}),
              direction(Direction::Up),
              speed(5) {

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

void Snake::grow() {
    if(direction == Direction::Up){
        SnakeSegment newHead{snakeHead.x,snakeHead.y-speed};
        snakeHead = newHead;
        snakeSegments.insert(snakeSegments.begin(),newHead);
    }
    if(direction == Direction::Down){
        SnakeSegment newHead{snakeHead.x,snakeHead.y+speed};
        snakeHead = newHead;
        snakeSegments.insert(snakeSegments.begin(),newHead);
    }
    if(direction == Direction::Left){
        SnakeSegment newHead{snakeHead.x-speed,snakeHead.y};
        snakeHead = newHead;
        snakeSegments.insert(snakeSegments.begin(),newHead);
    }
    if(direction == Direction::Right){
        SnakeSegment newHead{snakeHead.x+speed,snakeHead.y};
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

