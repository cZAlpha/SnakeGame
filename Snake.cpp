//
// Created by cZAlpha on 2/10/2024.
//

#include "Snake.h"

Snake::Snake() {
    length = 1;
    x = 0;
    y = 0;
}

Snake::Snake(int len, int x, int y) {
    if (len >= 1) {
        length = len;
    }
    this->x = x;
    this->y = y;
}

void Snake::setLength(int inputtedLength) {
    if (inputtedLength >= 1) {
        length = inputtedLength;
    }
}

void Snake::setLocation(int x, int y) {
    this->x = x;
    this->y = y;
}

int Snake::getLength() const {
    return length;
}

void Snake::incrementLength() {
    length++;
}

int Snake::getLocation() const {
    return x;
}

int Snake::getY() const {
    return y;
}

bool Snake::isCollidingWith(const Apple& apple) const {
    return x == apple.x && y == apple.y;
}
