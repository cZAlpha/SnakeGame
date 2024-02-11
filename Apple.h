//
// Created by Parents on 2/10/2024.
//

#ifndef APPLE_H
#define APPLE_H

class Apple {
    private:
        int value; // Default value is 0
        int x;      // X Coord
        int y;      // Y Coord

    public: // Public member functions
        Apple(); // Default Constructor
        Apple(int len, int x, int y); // Custom Constructor
        void setValue(int inputtedValue); // Setter for value
        void setLocation(int x, int y); // Setter for location
        int getLength(); // Getter for length
        void incrementLength(); // Increment length
        int getLocation(); // Getter for x
        int getY(); // Getter for y
};

#endif // APPLE_H

