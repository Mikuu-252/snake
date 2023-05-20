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
    int boardWidth;
    int boardHeight;
    SnakeSegment snakeHead;
    std::vector<SnakeSegment> snakeSegments;
    Direction direction;
    int speed;


    void setDirection(Direction newDirection);

public:
    Snake(int boardWidth, int boardHeight);
    void debugDisplay();

    void setSpeed(int speed);

    void move();
    void turn(Direction turn);
    void grow();

    const std::vector<SnakeSegment> &getSnakeSegments() const;
    int getSpeed() const;
    const SnakeSegment &getSnakeHead() const;
};


#endif //SNAKE_MW_SR17_272241_SNAKE_H
