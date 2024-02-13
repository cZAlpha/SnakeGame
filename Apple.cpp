//
// Created by cZAlpha on 2/10/2024.
//

#include "Apple.h"

Apple::Apple() {
    value = 1;
    x = 0;
    y = 0;
}

Apple::Apple(int len, int x, int y) {
    if (len >= 1) {
        value = len;
    }
    this->x = x;
    this->y = y;
}

    void Apple::setValue(int inputtedValue) {
        if (inputtedValue >= 1) {
            value = inputtedValue;
        }
    }

    void Apple::setLocation(int x, int y) {
        this->x = x;
        this->y = y;
    }

    int Apple::getLength() {
        return value;
    }

    void Apple::incrementLength() {
        value++;
    }

    int Apple::getX() const { // Implement getter function for x coordinate
        return x;
    }

    int Apple::getY() const { // Implement getter function for y coordinate
        return y;
    }
