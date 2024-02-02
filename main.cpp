//
// Created by Noah Klaus on 2/1/24.
//
// START - Imports
#include <iostream>
// STOP  - Imports

// START - Namespaces
using namespace std;
// STOP  - Namespaces

// START - Matrix Global Variables
const int rows = 20;
const int cols = 20;
// STOP  - Matrix Global Variables


// START - Classes
class Snake {
private: // Private member variables
    int length = 1; // Length of snake (size)
    int location[2]; // Array holding the x and y location of the snake

public: // Public member functions
    Snake()  { // Default Constructor
        location[0] = 0;
        location[1] = 0;
    }

    Snake(int len, int x, int y) { // Custom Constructor
        length = len;
        location[0] = x;
        location[1] = y;
    }

    void setLength(int inputtedLength){
        length = inputtedLength;
    }

    void setLocation(int x, int y) {
        location[0] = x;
        location[1] = y;
    }

    int getLength() {
        return length;
    }

    void incrementLength() {
        length++;
    }

    pair<int, int> getLocation() const {
        return make_pair(location[0], location[1]);
    }

    // Need a function to ascertain whether or not the snake is colliding with an Apple so that you can add points
}; // END OF: Snake Class

class Apple {
private:
    int value = 1; // Default value is 1
    int location[2]; // Array holding the x and y location of the snake

public:
    Apple() { // Default Constructor
        location[0] = 0;
        location[1] = 0;
    }

    Apple(int val, int x, int y) { // Default Constructor
        location[0] = x;
        location[1] = y;
        value = val;
    }

    void setLocation(int x, int y) {
        location[0] = x;
        location[1] = y;
    }

    pair<int, int> getLocation() const {
        return make_pair(location[0], location[1]);
    }
}; // END OF: Apple Class

class GameBoard {
private: // Private member variables
    char matrix[rows][cols]; // Big Matrix

    void makeOutlineOnMatrix() { // makeOutline: replaces the contents of the 2D array 'matrix' to put an outline on it when it is printed to the console
        for (int y = 0; y < rows; ++y) { // Puts a barrier around the outside of the matrix to indicates where you cannot go
            for (int x = 0; x < cols; ++x) {
                if ( (x == 0 && y == 0) || (x == (rows-1) && y == (cols-1) ) || ( x == 0 && y == (cols-1) || ( x == (rows-1) && y ==0 ) ) ) { // If at corners
                    matrix[y][x] = '+';
                } else if ( y == 0 ) { // If on top barrier
                    matrix[y][x] = '-';
                } else if ( x == 0 ) { // If on left barrier
                    matrix[y][x] = '|';
                } else if ( x == rows - 1 ){ // If on right barrier
                    matrix[y][x] = '|';
                } else if ( y == cols - 1) { // If on bottom barrier
                    matrix[y][x] = '-';
                } else { // If not on barrier (in play space) ; This  else statement is meant to replace the middle of the grid with a desired character
                    matrix[y][x] = ' '; // Placeholder char
                }
            }
        }
    }

public:
    GameBoard()  { // Default Constructor
        makeOutlineOnMatrix(); // Puts the outline on the matrix
    }

    void displayMatrix() {
        for (int i = 0; i < rows; ++i) { // Displays the matrix
            for (int j = 0; j < cols; ++j) {
                cout << matrix[i][j] << "  ";
            }
            cout << '\n';
        }
    } // END OF: displayMatrix()

    void placeSnake(Snake &snake) {
        int x = snake.getLocation().first;
        int y = snake.getLocation().second;

        if ((x >= 0) && (x < rows - 2) && (y >= 0) && (y < cols - 2)) {
            if (matrix[y + 1][x + 1] == 'A') {
                cout << snake.getLength() + 1 << endl; // DELETE AFTER TESTING
                snake.incrementLength(); // Increment the length directly
            }
            matrix[y + 1][x + 1] = 'S';
        } else {
            throw out_of_range("Snake Location (x,y) Out of Range.");
        }
    }

    void placeApple(Apple apple) { // ONLY PLACES THE HEAD OF THE SNAKE!
        int x = apple.getLocation().first;
        int y = apple.getLocation().second;

        if ( matrix[y + 1][x + 1] != ' ') {
            throw invalid_argument("Cannot Place Apple In An Occupied Index");
        } else if ( (x >= 0) && (x < rows - 2)  && (y >= 0) && (y < cols - 2) ) {
            matrix[y + 1][x + 1] = 'A';
        } else {
            throw out_of_range("Apple Location (x,y) Out of Range.");
        }
    } // END OF: placeSnake
}; // END OF: GameBoard Class
// STOP  - Classes



// START - Functions
void fillRandomChars(char myArray[][18], int numRows, int numCols) {
    const char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    const int charsetSize = sizeof(charset) - 1;

    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            int randomIndex = rand() % charsetSize;
            myArray[i][j] = charset[randomIndex];
        }
    }
} // END OF: fillRandomChars

void newLines(int numOfLines) { // Function that outputs a specified number of new lines (arg) to the console
    for (int i = 0; i < numOfLines; ++i) {
        cout << endl; // New line
    }
}

void clearScreen() { // Clears an amount of space that would be necessary for a new screen to be displayed
    newLines(35);
}

void basicTest() {
    // Instantiate objects of Snake class
    Snake snake1; // Default constructor
    Snake snake2(5, 17, 17); // Custom constructor

    Apple apple1; // Instantiate objects of Apple class
    Apple apple2(1, 2,3);

    GameBoard gameBoard; // Instantiate object of GameBoard class

    // Display information about the snakes
    cout << "Snake 1 Length: " << snake1.getLength() << endl;
    auto snake2Location = snake2.getLocation();
    cout << "Snake 2 Length: " << snake2.getLength() << ", Location: (" << snake2Location.first << ", " << snake2Location.second << ")" << endl;

    // Display information about the apples
    auto apple1Location = apple1.getLocation();
    cout << "Apple 1 Location: (" << apple1Location.first << ", " << apple1Location.second << ")" << endl;
    auto apple2Location = apple2.getLocation();
    cout << "Apple 2 Location: (" << apple2Location.first << ", " << apple2Location.second << ")" << endl;

    gameBoard.placeApple(apple1);
    gameBoard.placeApple(apple2);
    gameBoard.placeSnake(snake1);
    gameBoard.placeSnake(snake2);
    // Display the game board
    gameBoard.displayMatrix();

    cout << "Snake 1 Length: " << snake1.getLength() << endl;
    cout << "Snake 2 Length Before: " << snake2.getLength() << endl;
    snake2.setLength(3);
    cout << "Snake 2 Length After: " << snake2.getLength() << endl;
}
// STOP  - Functions


int main() {
    GameBoard gameBoard; // Instantiate object of GameBoard class
    for ( int i = 0 ; i < 10 ; i++ ) {
        gameBoard.displayMatrix();
        clearScreen();
    }

    return 0;
}