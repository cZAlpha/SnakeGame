//
// Created by Noah Klaus on 2/12/24.
//

#ifndef SNAKE_SPRITE_H
#define SNAKE_SPRITE_H

// START - Imports
#include <SDL.h>
// STOP - Imports

// START - Namespaces
using namespace std;
// STOP - Namespaces

// START - Sprite Class Header
class Sprite {
private:
    SDL_Texture* texture;
    SDL_Rect rect;
    int id;
public:
    Sprite(); // Default Constructor ; Should not really use this...
    Sprite(const char *imagePath, SDL_Renderer *renderer); // Custom Constructor ; Takes args of img path as char*
    void render(SDL_Renderer* renderer); // Render Sprite

    // Getters
    int getX();
    int getY();
    int getW();
    int getH();

    // Setters
    void setX(int x);
    void setY(int y);

    bool isCollidingWith(Sprite sprite) const;
};
// STOP - Sprite Class Header

#endif //SNAKE_SPRITE_H
