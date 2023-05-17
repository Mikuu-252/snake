#ifndef SNAKE_MW_SR17_272241_FOOD_H
#define SNAKE_MW_SR17_272241_FOOD_H

class Food {
    int boardWidth;
    int boardHeight;
    int x;
    int y;

public:
    Food(int boardWidth,int boardHeight);
    int getX() const;
    int getY() const;

};


#endif //SNAKE_MW_SR17_272241_FOOD_H
