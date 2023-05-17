#include <cstdlib>
#include "Food.h"

Food::Food(int boardWidth, int boardHeight): boardWidth(boardWidth), boardHeight(boardHeight) {
    x = rand() % boardWidth;
    y = rand() % boardHeight;
}

int Food::getX() const {
    return x;
}

int Food::getY() const {
    return y;
}
