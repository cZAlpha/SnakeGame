//
// Created by cZAlpha on 2/10/2024.
//

#include "Trashbag.h"

Trashbag::Trashbag() {
    this->setValue(1);
    this->setX(0);
    this->setY(0);
}

Trashbag::Trashbag(int value, int x, int y, SDL_Renderer* renderer) : Sprite("/Users/nbklaus21/CLionProjects/SnakeGame/Assets/trashbag_sprite.bmp", renderer) {
    if (value >= 1) { this->setValue(value); }
    this->setX(x);
    this->setY(y);
}

    void Trashbag::setValue(int inputtedValue) {
        if (inputtedValue >= 1) { this->value = inputtedValue; }
    }

    void Trashbag::setLocation(int x, int y) {
        this->setX(x);
        this->setY(y);
    }

    int Trashbag::getValue() { return this->value; }

    void Trashbag::incrementLength() { value++; }

    int Trashbag::getX() const { return this->x; }

    int Trashbag::getY() const { return this->y; }
