//
// Created by Noah Klaus on 2/1/24.
//

// START - Imports
#include <iostream>
#include <SDL.h>
#include "Sprite.h"
#include "Apple.h"
#include "Snake.h"
// STOP  - Imports

// START - Namespaces
using namespace std;
// STOP - Namespaces

// START - Global Variables
SDL_Window* window;
SDL_Renderer* renderer;
int FPS = 60;
// STOP  - Global Variables


// START - Functions
int calculateMilliseconds(int desiredFPS) { return 1000 / desiredFPS; }
// STOP - Functions


// START - Main
int main(int argc, char* argv[]) {
    cout << "Main Function Has Started." << endl;

    // START - Init. Local Variables
    int fps = calculateMilliseconds(FPS);
    int quit = 0;
    SDL_Event event;

    int w = 800;
    int h = 600;
    int windowed = 1; // Window flag, used for toggle window/fullscreen
    int test = 1; // Test flag, used to toggle restricted movement

    int result = SDL_Init(SDL_INIT_EVERYTHING);
    if (result < 0) return -1;
    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL); // Current Key State (what is being pressed)
    // STOP  - Init. Local Variables

    // START - Error Checking
    Uint32 flags = SDL_WINDOW_SHOWN;
    window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, flags);
    if (window == NULL) {
        cerr << "Failed to create window: " << SDL_GetError() << endl;
        SDL_Quit();
        return -1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        cerr << "Failed to create renderer: " << SDL_GetError() << endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }
    // STOP  - Error Checking

    // START - Sprites
    Sprite testSprite("/Users/nbklaus21/Desktop/testSprite.bmp", renderer); // Test Sprite
    // STOP  - Sprites

    // START - Game Loop
    while (!quit) { // game loop
        SDL_PumpEvents(); // Update the state of all keys

        // START - System Keys
        while ( SDL_PollEvent( &event ) != 0 ) { // If an event is encountered
            switch (event.type) { // Logic Flow using switch cases
                case SDL_WINDOWEVENT_SIZE_CHANGED:  // Handles window size changing
                    w = event.window.data1;
                    h = event.window.data2;
                    SDL_RenderPresent(renderer);
                    break; // END SDL_WINDOWEVENT_SIZE_CHANGED CASE
                case SDL_QUIT: // If the quit button is clicked, exit game
                    quit = 1;
                    break; // END SDL_QUIT CASE
                case SDL_KEYUP: // If a key is pressed
                    switch (event.key.keysym.sym) { // Gets the specific key that is pressed
                        // START - System/Window Changes From Key Press
                        case SDLK_ESCAPE: // If the escape key is pressed, quit game
                            quit = 1;
                            break; // END SDLK_ESCAPE CASE
                        case SDLK_F1: // If 'F1' key is pressed, go into fullscreen mode
                            // THE FOLLOWING CODE CAUSES THE SCREEN TO BUG THE FUCK OUT (Only  n OSX)
                            windowed = !windowed;
                            if (windowed) { SDL_SetWindowFullscreen(window, SDL_FALSE); }
                            else { SDL_SetWindowFullscreen(window, SDL_TRUE); }
                            break; // END SDLK_F1 CASE
                            // STOP  - System/Window Changes From Key Press
                    }
                    break; // END SDL_KEYUP CASE
            } // END SWITCH CASE LOGIC FLOW
        } // END OF CHECKING FOR KEY PRESSES
        // STOP  - System Keys

        SDL_SetRenderDrawColor(renderer, 20, 200, 20, 255); // Makes the screen green
        SDL_RenderClear(renderer);

        // Render TestSprite
        testSprite.render(renderer);

        SDL_RenderPresent(renderer);
        SDL_Delay(fps); // updates every 10 ms which is
    } // END OF GAME LOOP
    // STOP  - Game Loop

    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
// STOP  - Main
