//
// Created by Noah Klaus on 2/1/24.
//

// START - Imports
#include <iostream>
#include <SDL.h>
#include <ctime>
#include "Sprite.h"
#include "Trashbag.h"
#include "Trashman.h"
#include "cstdlib"
// STOP  - Imports

// START - Namespaces
using namespace std;
// STOP - Namespaces

// START - Global Variables
SDL_Window* window;
SDL_Renderer* renderer;
int FPS = 60;
int w = 800; // Window Width
int h = 600; // Window Height
// STOP  - Global Variables


// START - Functions
int calculateMilliseconds(int desiredFPS) { return 1000 / desiredFPS; }

int randomNum(int max) { // Function that generates a random number up to the number inputted as an argument (max)
    int randomNum = rand() % max; // Generate a random number between 0 and max
    return randomNum;
}
// STOP - Functions


// START - Main
int main(int argc, char* argv[]) {
    cout << "Main Function Has Started." << endl;
    srand(time(nullptr)); // Seed the random number generator with the current time

    // START - Init. Local Variables
    int fps = calculateMilliseconds(FPS);
    int quit = 0;
    SDL_Event event;

    Trashbag* trashbagArray[5]; // Array to hold apples
    int moveAmount = 10;
    int windowed = 1; // Window flag, used for toggle window/fullscreen
    int test = 1; // Test flag, used to toggle restricted movement

    int result = SDL_Init(SDL_INIT_EVERYTHING);
    if (result < 0) return -1;
    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL); // Current Key State (what is being pressed)
    // STOP  - Init. Local Variables

    // START - Error Checking
    Uint32 flags = SDL_WINDOW_SHOWN;
    window = SDL_CreateWindow("Trash Man Simulator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, flags);
    if (window == NULL) {
        cerr << "Failed to create window: " << SDL_GetError() << endl;
        SDL_Quit();
        return -1;
    }

    // Check SDL_ttf for rendering text error
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        cerr << "Failed to create renderer: " << SDL_GetError() << endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }
    // STOP  - Error Checking

    // START - State Vars
    bool inMainMenu = true;
    bool startGame = false;
    // STOP - State Vars

    // START - Sprites
    Sprite mainmenutitle("/Users/nbklaus21/CLionProjects/SnakeGame/Assets/mainmenutitle_sprite.bmp", renderer); // Main menu title Sprite

    Trashman trashman(500, 10, renderer); // Trashman Sprite

    // Instantiate and fill Trashbag array with Trashbags
    for (int i = 0; i < 5; i++) {
        trashbagArray[i] = new Trashbag(1, randomNum(w - 50), randomNum(h - 50), renderer); // Dynamically allocate memory
    }
    // STOP  - Sprites

    // State checking
    if (inMainMenu == true and startGame == false) { // If in main menu
        // START - Main Menu
        while (!quit) { // Main Menu Loop
            SDL_PumpEvents(); // Update the state of all keys

            // START - System Keys
            while (SDL_PollEvent(&event) != 0) { // If an event is encountered
                switch (event.type) { // Logic Flow using switch cases
                    case SDL_WINDOWEVENT_SIZE_CHANGED:  // Handles window size changing
                        w = event.window.data1;
                        h = event.window.data2;
                        SDL_RenderPresent(renderer);
                        break; // END SDL_WINDOWEVENT_SIZE_CHANGED CASE
                    case SDL_QUIT: // If the quit button is clicked, exit game
                        quit = 1;
                        break; // END SDL_QUIT CASE
                    case SDL_KEYUP: // If a key is pressed and released
                        switch (event.key.keysym.sym) { // Gets the specific key that is pressed
                            // START - System/Window Changes From Key Press
                            case SDLK_ESCAPE: // If the escape key is pressed, quit game
                                quit = 1;
                                break;
                            case SDLK_F1: // If 'F1' key is pressed, go into fullscreen mode
                                // THE FOLLOWING CODE CAUSES THE SCREEN TO BUG THE FUCK OUT (Only on OSX)
                                windowed = !windowed;
                                if (windowed) { SDL_SetWindowFullscreen(window, SDL_FALSE); }
                                else { SDL_SetWindowFullscreen(window, SDL_TRUE); }
                                break; // END SDLK_F1 CASE
                                break; // END SDL_KEYUP CASE
                        }    // STOP  - System/Window Changes From Key Press
                        break; // END SDL_KEYDOWN CASE
                } // END SWITCH CASE LOGIC FLOW
            } // END OF CHECKING FOR KEY PRESSES

            // Background Rendering
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Makes the screen green
            SDL_RenderClear(renderer);

            // Put main menu sprites on the screen
            mainmenutitle.setX( (w/2) - (mainmenutitle.getW() / 2) );
            mainmenutitle.setY( (h/2) - (mainmenutitle.getH() / 2) - 100 );
            // Render Main menu Sprites
            mainmenutitle.render(renderer);

            // Magical doohickey stuff
            SDL_RenderPresent(renderer);
            SDL_Delay(fps); // updates every 10 ms which is
        }// STOP  - Main Menu Loop
        // STOP - Main Menu
        inMainMenu = false;
        startGame = true;
    }
    else if (startGame == true and inMainMenu == false) { // If in game
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
                    case SDL_KEYUP: // If a key is pressed and released
                        switch (event.key.keysym.sym) { // Gets the specific key that is pressed
                            // START - System/Window Changes From Key Press
                            case SDLK_ESCAPE: // If the escape key is pressed, quit game
                                quit = 1;
                                break;
                            case SDLK_F1: // If 'F1' key is pressed, go into fullscreen mode
                                // THE FOLLOWING CODE CAUSES THE SCREEN TO BUG THE FUCK OUT (Only on OSX)
                                windowed = !windowed;
                                if (windowed) { SDL_SetWindowFullscreen(window, SDL_FALSE); }
                                else { SDL_SetWindowFullscreen(window, SDL_TRUE); }
                                break; // END SDLK_F1 CASE
                                break; // END SDL_KEYUP CASE
                        }    // STOP  - System/Window Changes From Key Press
                    case SDL_KEYDOWN: // If a key is pressed down
                        switch (event.key.keysym.sym) { // Gets the specific key that is pressed
                            case SDLK_w: // W key
                                if (trashman.getX() >= 0 and trashman.getY() >= 0 and trashman.getX() <= w and trashman.getY() <= h ) {
                                    trashman.setLocation(trashman.getX(), trashman.getY() - moveAmount); // Moves the snake up
                                }
                                break;
                            case SDLK_s: // S key
                                if (trashman.getX() >= 0 and trashman.getY() >= 0 and trashman.getX() <= w and trashman.getY() <= h ) {
                                    trashman.setLocation(trashman.getX(), trashman.getY() + moveAmount); // Moves the snake down
                                }
                                break;
                            case SDLK_a: // A key
                                if (trashman.getX() >= 0 and trashman.getY() >= 0 and trashman.getX() <= w and trashman.getY() <= h ) {
                                    trashman.setLocation(trashman.getX() - moveAmount, trashman.getY()); // Moves the snake left
                                }
                                break;
                            case SDLK_d: // D key
                                if (trashman.getX() >= 0 and trashman.getY() >= 0 and trashman.getX() <= w and trashman.getY() <= h ) {
                                    trashman.setLocation(trashman.getX() + moveAmount, trashman.getY()); // Moves the snake right
                                }
                                break;
                        }
                        break; // END SDL_KEYDOWN CASE

                } // END SWITCH CASE LOGIC FLOW
            } // END OF CHECKING FOR KEY PRESSES
            // STOP  - System Keys

            SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255); // Makes the screen green
            SDL_RenderClear(renderer);

            // Render Test Sprites
            trashman.render(renderer);
            // Render all apples
            for (int i = 0; i < 5; ++i) {
                trashbagArray[i]->render(renderer);
            }

            // Collision w/ Apples
            for (int i = 0; i < 5; ++i) {
                if ( trashman.isCollidingWith(*trashbagArray[i]) ) {
                    trashbagArray[i]->setLocation(0, 0);
                }
            }
            // Out of Bounds Collision w/ Trashman
            if (trashman.getX() < 0 ) {
                trashman.setLocation(w - trashman.getW(), trashman.getY()); // Puts snake at left side of screen
            }
            if (trashman.getY() < 0 ) { // If snake is out of bounds on top of screen
                trashman.setLocation(trashman.getX(), h - trashman.getH()); // Puts snake at left side of screen
            }
            if (trashman.getX() > (w - trashman.getW()) ) { // If snake is out of bounds on right side
                trashman.setLocation(0, trashman.getY()); // Puts snake at left side of screen
            }
            if (trashman.getY() > (h - trashman.getH()) ) { // If snake is out of bounds on bottom
                trashman.setLocation(trashman.getX(), 0); // Puts snake at top of screen
            }

            // Magical doohickey stuff
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
}
// STOP  - Main
