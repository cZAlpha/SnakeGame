//
// Created by cZAlpha on 2/10/2024.
//

#include "Apple.h"

Apple::Apple() {
    this->setValue(1);
    this->setX(0);
    this->setY(0);
}

Apple::Apple(int value, int x, int y, SDL_Renderer* renderer) : Sprite("/Users/nbklaus21/CLionProjects/SnakeGame/Assets/testSprite.bmp", renderer) {
    if (value >= 1) { this->setValue(value); }
    this->setX(x);
    this->setY(y);
}

    void Apple::setValue(int inputtedValue) {
        if (inputtedValue >= 1) { this->value = inputtedValue; }
    }

    void Apple::setLocation(int x, int y) {
        this->setX(x);
        this->setY(y);
    }

    int Apple::getValue() { return this->value; }

    void Apple::incrementLength() { value++; }

    int Apple::getX() const { return this->x; }

    int Apple::getY() const { return this->y; }
