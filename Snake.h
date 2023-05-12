#ifndef SNAKE_MW_SR17_272241_SNAKE_H
#define SNAKE_MW_SR17_272241_SNAKE_H

#include <vector>

struct SnakeSegment {
    int x;
    int y;
};

enum Direction {
    Up,
    Down,
    Left,
    Right
};

class Snake {
    int boardSize;
    SnakeSegment snakeHead;
    std::vector<SnakeSegment> snakeSegments;
    Direction direction;
    int speed;
    bool gameEnd;
    void setDirection(Direction newDirection);

public:
    Snake(int boardSize);
    void debugDisplay();
    void move();
    void turn(Direction turn);
};


#endif //SNAKE_MW_SR17_272241_SNAKE_H
