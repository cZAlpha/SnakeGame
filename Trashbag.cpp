//
// Created by cZAlpha on 2/10/2024.
//

#include "Trashbag.h"

Trashbag::Trashbag() {
    this->setX(0);
    this->setY(0);
}

Trashbag::Trashbag(int x, int y, SDL_Renderer* renderer) : Sprite("/Users/nbklaus21/CLionProjects/SnakeGame/Assets/trashbag_sprite.bmp", renderer) {
    this->setX(x);
    this->setY(y);
}

    void Trashbag::setLocation(int x, int y) {
        this->setX(x);
        this->setY(y);
    }

    void Trashbag::incrementLength() { value++; }
