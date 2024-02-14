//
// Created by cZAlpha on 2/10/2024.
//

#include "Snake.h"
#include <SDL.h>
#include "Sprite.h"

Snake::Snake() : Sprite() { // Default constructor
    length = 1;
    x = 0;
    y = 0;
}

Snake::Snake(int len, int x, int y, SDL_Renderer* renderer) : Sprite("/Users/nbklaus21/CLionProjects/SnakeGame/Assets/snake_head_sprite.bmp", renderer) { // Full custom constructor
    if (len >= 1) {
        length = len;
    }
    this->setX(x);
    this->setY(y);
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

