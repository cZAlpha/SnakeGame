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
#include "Tracker.h"
#include "cstdlib"
#include <thread> // For time
#include <chrono> // For time
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
int numOfTrashBags = 1; // Number of trashbags to be instantiated
// STOP  - Global Variables


// START - Functions
int calculateMilliseconds(int desiredFPS = 60) {
    if (desiredFPS != 0) {
        return 1000 / desiredFPS;
    } else {
        return 0; // Handle zero case to avoid error
    }}

int randomNum(int max) { // Function that generates a random number up to the number inputted as an argument (max)
    int randomNum = rand() % max; // Generate a random number between 0 and max
    return randomNum;
}
// STOP - Functions


// START - Main
int main(int argc, char* argv[]) {
    cout << "~|main function has started|~" << endl;
    srand(time(nullptr)); // Seed the random number generator with the current time

    // START - Init. Local Variables
    int fps = calculateMilliseconds(FPS);
    bool mainmenu = true; // main menu state var
    bool level1 = true; // level1 state var
    bool level2 = true; // level2 state var
    bool win = false;
    SDL_Event event;

    Trashbag* trashbagArray[numOfTrashBags]; // Array to hold apples
    int numOfBagsAcquired = 0; // number of bags the user has acquired
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

    // START - Sprites
    Sprite level1gamebackground("/Users/nbklaus21/CLionProjects/SnakeGame/Assets/level1background_sprite.bmp", renderer); // The sprite that acts as the background to the level1
    level1gamebackground.setX(0);
    level1gamebackground.setY(0);
    Sprite level2gamebackground("/Users/nbklaus21/CLionProjects/SnakeGame/Assets/level2background_sprite.bmp", renderer); // The sprite that acts as the background to the level1
    level2gamebackground.setX(0);
    level2gamebackground.setY(0);
    Sprite mainmenutitle("/Users/nbklaus21/CLionProjects/SnakeGame/Assets/mainmenutitle_sprite.bmp", renderer); // Main menu title Sprite
    Sprite mainmenuprompt("/Users/nbklaus21/CLionProjects/SnakeGame/Assets/mainmenuprompt_sprite.bmp", renderer); // Main menu prompt Sprite
    Sprite youwontext("/Users/nbklaus21/CLionProjects/SnakeGame/Assets/youwon_sprite.bmp", renderer); // Main menu prompt Sprite
    Trashman trashman(500, 10, renderer); // Trashman Sprite

    // Tracker object instantiation
    Tracker tracker;

    // Instantiate and fill Trashbag array with Trashbags
    for (int i = 0; i < numOfTrashBags; i++) {
        int yPos = randomNum(h - 50);
        if ( yPos < 80 ) {
            yPos += 80;
        }
        int xPos = randomNum(w - 50);
        trashbagArray[i] = new Trashbag(xPos, yPos, renderer); // Dynamically allocate memory
    }
    // STOP  - Sprites

    // START - Main Menu
    cout << "~|main menu has started|~" << endl;
    while (mainmenu) { // Main Menu Loop
        SDL_PumpEvents(); // Update the state of all keys

        // START - System Keys
        while (SDL_PollEvent(&event) != 0) { // If an event is encountered
            switch (event.type) { // Logic Flow using switch cases
                case SDL_WINDOWEVENT_SIZE_CHANGED:  // Handles window size changing
                    w = event.window.data1;
                    h = event.window.data2;
                    SDL_RenderPresent(renderer);
                    break; // END SDL_WINDOWEVENT_SIZE_CHANGED CASE
                case SDL_QUIT: // If the mainmenu button is clicked, exit level1
                    mainmenu = false;
                    level1 = false;
                    level2 = false;
                    break; // END SDL_QUIT CASE
                case SDL_KEYUP: // If a key is pressed and released
                    switch (event.key.keysym.sym) { // Gets the specific key that is pressed
                        case SDLK_ESCAPE: // If the escape key is pressed, mainmenu level1
                            cout << "escape was pressed" << endl;
                            mainmenu = false;
                            level1 = false;
                            level2 = false;
                            break;
                        case SDLK_F1: // If 'F1' key is pressed, go into fullscreen mode
                            // THE FOLLOWING CODE CAUSES THE SCREEN TO BUG THE FUCK OUT (Only on OSX)
                            windowed = !windowed;
                            if (windowed) { SDL_SetWindowFullscreen(window, SDL_FALSE); }
                            else { SDL_SetWindowFullscreen(window, SDL_TRUE); }
                            break; // END SDLK_F1 CASE
                        case SDLK_RETURN: // If 'return' key is pressed, switch to level1 loop
                            cout << "return was pressed" << endl;
                            mainmenu = false;
                            break; // END SDLK_RETURN CASE
                    }    // STOP  - System/Window Changes From Key Press
                    break; // END SDL_KEYDOWN CASE
            } // END SWITCH CASE LOGIC FLOW
        } // END OF CHECKING FOR KEY PRESSES

        // Background Rendering
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Makes the screen green
        SDL_RenderClear(renderer);

        // Put main menu sprites on the screen
        mainmenutitle.setX((w / 2) - (mainmenutitle.getW() / 2));
        mainmenutitle.setY((h / 2) - (mainmenutitle.getH() / 2) - 100);
        mainmenuprompt.setX((w / 2) - (mainmenuprompt.getW() / 2));
        mainmenuprompt.setY((h / 2) - (mainmenuprompt.getH() / 2) - 20);
        // Render Main menu Sprites
        mainmenutitle.render(renderer);
        mainmenuprompt.render(renderer);

        // Magical doohickey stuff
        SDL_RenderPresent(renderer);
        SDL_Delay(fps); // updates every 10 ms which is
    }// STOP  - Main Menu Loop
    cout << "~|main menu loop has ended|~" << endl;
    // STOP - Main Menu

    // START - Level 1 Game Loop
    cout << "~|level1 loop has started|~" << endl;
    int level1bagstorageXPos = 100;
    int level1bagstorageYPos = 50;
    while (level1 and numOfBagsAcquired < numOfTrashBags) { // level1 loop
        SDL_PumpEvents(); // Update the state of all keys

        // START - System Keys
        while ( SDL_PollEvent( &event ) != 0 ) { // If an event is encountered
            switch (event.type) { // Logic Flow using switch cases
                case SDL_WINDOWEVENT_SIZE_CHANGED:  // Handles window size changing
                    w = event.window.data1;
                    h = event.window.data2;
                    SDL_RenderPresent(renderer);
                    break; // END SDL_WINDOWEVENT_SIZE_CHANGED CASE
                case SDL_QUIT: // If the mainmenu button is clicked, exit level1
                    level1 = false;
                    level2 = false;
                    break; // END SDL_QUIT CASE
                case SDL_KEYUP: // If a key is pressed and released
                    switch (event.key.keysym.sym) { // Gets the specific key that is pressed
                        // START - System/Window Changes From Key Press
                        case SDLK_ESCAPE: // If the escape key is pressed, exit
                            cout << "escape was pressed" << endl;
                            level1 = false;
                            level2 = false;
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
                        case SDLK_UP:
                            if (trashman.getX() >= 0 and trashman.getY() >= 0 and trashman.getX() <= w and trashman.getY() <= h ) {
                                trashman.setLocation(trashman.getX(), trashman.getY() - moveAmount); // Moves the snake up
                            }
                            break;
                        case SDLK_DOWN:
                            if (trashman.getX() >= 0 and trashman.getY() >= 0 and trashman.getX() <= w and trashman.getY() <= h ) {
                                trashman.setLocation(trashman.getX(), trashman.getY() + moveAmount); // Moves the snake down
                            }
                            break;
                        case SDLK_LEFT:
                            if (trashman.getX() >= 0 and trashman.getY() >= 0 and trashman.getX() <= w and trashman.getY() <= h ) {
                                trashman.setLocation(trashman.getX() - moveAmount, trashman.getY()); // Moves the snake left
                            }
                            break;
                        case SDLK_RIGHT:
                            if (trashman.getX() >= 0 and trashman.getY() >= 0 and trashman.getX() <= w and trashman.getY() <= h ) {
                                trashman.setLocation(trashman.getX() + moveAmount, trashman.getY()); // Moves the snake right
                            }
                            break;
                    }
                    break; // END SDL_KEYDOWN CASE

            } // END SWITCH CASE LOGIC FLOW
        } // END OF CHECKING FOR KEY PRESSES
        // STOP  - System Keys

        SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255); // Screen background color
        SDL_RenderClear(renderer);
        level1gamebackground.render(renderer); // Renders the background

        // Render all trashbags
        for (int i = 0; i < numOfTrashBags; ++i) {
            trashbagArray[i]->render(renderer);
        }
        // Render Trashman Sprite
        trashman.render(renderer);

        // Collision w/ trash bags
        for (int i = 0; i < numOfTrashBags; ++i) {
            if ( trashman.isCollidingWith(*trashbagArray[i]) and
            (trashbagArray[i]->getX() != level1bagstorageXPos or
            trashbagArray[i]->getY() != level1bagstorageYPos)) {
                cout << "Trash bag acquired" << endl;
                trashbagArray[i]->setLocation(level1bagstorageXPos, level1bagstorageYPos); // places trash in trash can
                numOfBagsAcquired++;
                trashman.incrementTrash();
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

        // Check for console dialogue
        if ( numOfBagsAcquired >= numOfTrashBags ) {
            win = true;
            level1 = false;
            cout << "You won!" << endl;
            this_thread::sleep_for(chrono::seconds(1/2)); // Sleep for 2 seconds after you win for dramatic effect
        }
        // Magical doohickey stuff
        SDL_RenderPresent(renderer);
        SDL_Delay(fps); // updates every 10 ms which is
    } // END OF GAME LOOP
    // After level 1 ends
    int level1Trash = trashman.getTrash(); // Assuming getTrash() returns an integer
    tracker.append(1, level1Trash);
    cout << "~|level1 loop has ended|~" << endl;
    // STOP  - Level 1 Game Loop

    // START - Win Screen
    cout << "~|win screen has started|~" << endl;
    while (win) { // Win Screen Loop
        SDL_PumpEvents(); // Update the state of all keys

        // START - System Keys
        while (SDL_PollEvent(&event) != 0) { // If an event is encountered
            switch (event.type) { // Logic Flow using switch cases
                case SDL_WINDOWEVENT_SIZE_CHANGED:  // Handles window size changing
                    w = event.window.data1;
                    h = event.window.data2;
                    SDL_RenderPresent(renderer);
                    break; // END SDL_WINDOWEVENT_SIZE_CHANGED CASE
                case SDL_QUIT: // If the mainmenu button is clicked, exit level1
                    cout << "quit was pressed" << endl;
                    win = false;
                    break; // END SDL_QUIT CASE
                case SDL_KEYUP: // If a key is pressed and released
                    switch (event.key.keysym.sym) { // Gets the specific key that is pressed
                        case SDLK_ESCAPE: // If the escape key is pressed, mainmenu level1
                            cout << "escape was pressed" << endl;
                            win = false;
                            break;
                        case SDLK_F1: // If 'F1' key is pressed, go into fullscreen mode
                            // THE FOLLOWING CODE CAUSES THE SCREEN TO BUG THE FUCK OUT (Only on OSX)
                            windowed = !windowed;
                            if (windowed) { SDL_SetWindowFullscreen(window, SDL_FALSE); }
                            else { SDL_SetWindowFullscreen(window, SDL_TRUE); }
                            break; // END SDLK_F1 CASE
                        case SDLK_RETURN: // If 'return' key is pressed, switch to level1 loop
                            cout << "return was pressed" << endl;
                            win = false;
                            break; // END SDLK_RETURN CASE
                    }    // STOP  - System/Window Changes From Key Press
                    break; // END SDL_KEYDOWN CASE
            } // END SWITCH CASE LOGIC FLOW
        } // END OF CHECKING FOR KEY PRESSES

        // Background Rendering
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Makes the screen green
        SDL_RenderClear(renderer);

        // Put you won screen sprites on the screen
        mainmenutitle.setX((w / 2) - (mainmenutitle.getW() / 2));
        mainmenutitle.setY((h / 2) - (mainmenutitle.getH() / 2) - 100);
        mainmenuprompt.setX((w / 2) - (mainmenuprompt.getW() / 2));
        mainmenuprompt.setY((h / 2) - (mainmenuprompt.getH() / 2));
        youwontext.setX((w / 2) - (youwontext.getW() / 2));
        youwontext.setY((h / 2) - (youwontext.getH() / 2) - 50);
        // Render Win Screen Sprites
        mainmenutitle.render(renderer);
        youwontext.render(renderer);
        mainmenuprompt.render(renderer);

        // Magical doohickey stuff
        SDL_RenderPresent(renderer);
        SDL_Delay(fps); // updates every 10 ms which is
    }// STOP  - Win Screen Loop
    cout << "~|win screen has ended|~" << endl;
    // STOP - Win Screen

    // START - Level 2 Game Loop
    cout << "~|level2 loop has started|~" << endl;
    int level2bagstorageXPos = 100;
    int level2bagstorageYPos = 65;
    numOfBagsAcquired = 0;
    // Randomize position of trashbags
    for (int i = 0; i < numOfTrashBags; i++) {
        int yPos = randomNum(h - 50);
        if ( yPos < 80 ) {
            yPos += 80;
        }
        int xPos = randomNum(w - 50);
        trashbagArray[i] = new Trashbag(xPos, yPos, renderer); // Dynamically allocate memory
    }
    while (level2 and numOfBagsAcquired < numOfTrashBags) { // level1 loop
        SDL_PumpEvents(); // Update the state of all keys

        // START - System Keys
        while ( SDL_PollEvent( &event ) != 0 ) { // If an event is encountered
            switch (event.type) { // Logic Flow using switch cases
                case SDL_WINDOWEVENT_SIZE_CHANGED:  // Handles window size changing
                    w = event.window.data1;
                    h = event.window.data2;
                    SDL_RenderPresent(renderer);
                    break; // END SDL_WINDOWEVENT_SIZE_CHANGED CASE
                case SDL_QUIT: // If the mainmenu button is clicked, exit level1
                    level2 = false;
                    break; // END SDL_QUIT CASE
                case SDL_KEYUP: // If a key is pressed and released
                    switch (event.key.keysym.sym) { // Gets the specific key that is pressed
                        // START - System/Window Changes From Key Press
                        case SDLK_ESCAPE: // If the escape key is pressed, mainmenu level1
                            cout << "escape was pressed" << endl;
                            level2 = false;
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
                        case SDLK_UP:
                            if (trashman.getX() >= 0 and trashman.getY() >= 0 and trashman.getX() <= w and trashman.getY() <= h ) {
                                trashman.setLocation(trashman.getX(), trashman.getY() - moveAmount); // Moves the snake up
                            }
                            break;
                        case SDLK_DOWN:
                            if (trashman.getX() >= 0 and trashman.getY() >= 0 and trashman.getX() <= w and trashman.getY() <= h ) {
                                trashman.setLocation(trashman.getX(), trashman.getY() + moveAmount); // Moves the snake down
                            }
                            break;
                        case SDLK_LEFT:
                            if (trashman.getX() >= 0 and trashman.getY() >= 0 and trashman.getX() <= w and trashman.getY() <= h ) {
                                trashman.setLocation(trashman.getX() - moveAmount, trashman.getY()); // Moves the snake left
                            }
                            break;
                        case SDLK_RIGHT:
                            if (trashman.getX() >= 0 and trashman.getY() >= 0 and trashman.getX() <= w and trashman.getY() <= h ) {
                                trashman.setLocation(trashman.getX() + moveAmount, trashman.getY()); // Moves the snake right
                            }
                            break;
                    }
                    break; // END SDL_KEYDOWN CASE

            } // END SWITCH CASE LOGIC FLOW
        } // END OF CHECKING FOR KEY PRESSES
        // STOP  - System Keys

        SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255); // Screen background color
        SDL_RenderClear(renderer);
        level2gamebackground.render(renderer); // Renders the background

        // Render all trashbags
        for (int i = 0; i < numOfTrashBags; ++i) {
            trashbagArray[i]->render(renderer);
        }
        // Render Trashman Sprite
        trashman.render(renderer);

        // Collision w/ trash bags
        for (int i = 0; i < numOfTrashBags; ++i) {
            if ( trashman.isCollidingWith(*trashbagArray[i]) and
                 (trashbagArray[i]->getX() != level2bagstorageXPos or
                  trashbagArray[i]->getY() != level2bagstorageYPos)) {
                cout << "Trash bag acquired" << endl;
                trashbagArray[i]->setLocation(level2bagstorageXPos, level2bagstorageYPos); // places trash in trash can
                cout << "(" << trashbagArray[i]->getX() << "," << trashbagArray[i]->getY() << ")" << endl;
                numOfBagsAcquired++;
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

        // Check for console dialogue
        if ( numOfBagsAcquired >= numOfTrashBags ) {
            win = true;
            level1 = false;
            cout << "You won level 2!" << endl;
            this_thread::sleep_for(chrono::seconds(1/2)); // Sleep for 2 seconds after you win for dramatic effect
        }
        // Magical doohickey stuff
        SDL_RenderPresent(renderer);
        SDL_Delay(fps); // updates every 10 ms which is
    } // END OF GAME LOOP
    // After level 2 ends
    int level2Trash = trashman.getTrash(); // Assuming getTrash() returns an integer
    tracker.append(2, level2Trash);
    cout << "~|level2 loop has ended|~" << endl;
    // STOP  - Level 2 Game Loop

    // START - Win Screen
    cout << "~|win screen has started|~" << endl;
    while (win) { // Win Screen Loop
        SDL_PumpEvents(); // Update the state of all keys

        // START - System Keys
        while (SDL_PollEvent(&event) != 0) { // If an event is encountered
            switch (event.type) { // Logic Flow using switch cases
                case SDL_WINDOWEVENT_SIZE_CHANGED:  // Handles window size changing
                    w = event.window.data1;
                    h = event.window.data2;
                    SDL_RenderPresent(renderer);
                    break; // END SDL_WINDOWEVENT_SIZE_CHANGED CASE
                case SDL_QUIT: // If the mainmenu button is clicked, exit level1
                    cout << "quit was pressed" << endl;
                    win = false;
                    break; // END SDL_QUIT CASE
                case SDL_KEYUP: // If a key is pressed and released
                    switch (event.key.keysym.sym) { // Gets the specific key that is pressed
                        case SDLK_ESCAPE: // If the escape key is pressed, mainmenu level1
                            cout << "escape was pressed" << endl;
                            win = false;
                            break;
                        case SDLK_F1: // If 'F1' key is pressed, go into fullscreen mode
                            // THE FOLLOWING CODE CAUSES THE SCREEN TO BUG THE FUCK OUT (Only on OSX)
                            windowed = !windowed;
                            if (windowed) { SDL_SetWindowFullscreen(window, SDL_FALSE); }
                            else { SDL_SetWindowFullscreen(window, SDL_TRUE); }
                            break; // END SDLK_F1 CASE
                        case SDLK_RETURN: // If 'return' key is pressed, switch to level1 loop
                            cout << "return was pressed" << endl;
                            win = false;
                            break; // END SDLK_RETURN CASE
                    }    // STOP  - System/Window Changes From Key Press
                    break; // END SDL_KEYDOWN CASE
            } // END SWITCH CASE LOGIC FLOW
        } // END OF CHECKING FOR KEY PRESSES

        // Background Rendering
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Makes the screen green
        SDL_RenderClear(renderer);

        // Put you won screen sprites on the screen
        mainmenutitle.setX((w / 2) - (mainmenutitle.getW() / 2));
        mainmenutitle.setY((h / 2) - (mainmenutitle.getH() / 2) - 100);
        mainmenuprompt.setX((w / 2) - (mainmenuprompt.getW() / 2));
        mainmenuprompt.setY((h / 2) - (mainmenuprompt.getH() / 2));
        youwontext.setX((w / 2) - (youwontext.getW() / 2));
        youwontext.setY((h / 2) - (youwontext.getH() / 2) - 50);
        // Render Win Screen Sprites
        mainmenutitle.render(renderer);
        youwontext.render(renderer);
        mainmenuprompt.render(renderer);

        // Magical doohickey stuff
        SDL_RenderPresent(renderer);
        SDL_Delay(fps); // updates every 10 ms which is
    }// STOP  - Win Screen Loop
    cout << "~|win screen has ended|~" << endl;
    // STOP - Win Screen

    // Tracker Status Update To Console
    tracker.printStatus();

    // Cleanup
    cout << "~|cleanup|~" << endl;
    // Free dynamically allocated memory
    for (int i = 0; i < numOfTrashBags; ++i) {
        delete trashbagArray[i];
        trashbagArray[i] = nullptr;
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    cout << "~|shutting down|~" << endl;
    return 0;
}
// STOP  - Main
