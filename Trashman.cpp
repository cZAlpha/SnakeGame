//
// Created by Noah Klaus on 2/10/2024.
//

#include "Trashman.h"
#include "Sprite.h"
#include <SDL.h>

Trashman::Trashman() : Sprite() { // Default constructor
    length = 1;
    x = 0;
    y = 0;
}

Trashman::Trashman(int x, int y, SDL_Renderer* renderer) : Sprite("/Users/nbklaus21/CLionProjects/SnakeGame/Assets/trashman_sprite.bmp", renderer) { // Full custom constructor
    this->setX(x);
    this->setY(y);
}

    void Trashman::setLength(int inputtedLength) {
        if (inputtedLength >= 1) {
            length = inputtedLength;
        }
    }

    void Trashman::setLocation(int x, int y) {
        this->setX(x);
        this->setY(y);
    }

    int Trashman::getLength() const {
        return length;
    }

    void Trashman::incrementLength() {
        length++;
    }

