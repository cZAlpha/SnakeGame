//
// Created by Noah Klaus on 4/23/24.
//

#ifndef TRASH_TRACKER_H
#define TRASH_TRACKER_H

#include <iostream>

class Tracker {
private:
    struct Node {
        int level;
        int trashBags;
        Node* next;
    };
    Node* head;

public:
    Tracker(); // Constructor
    ~Tracker(); // Destructor

    void append(int level, int bagsCollected);

    // Print the current status of trash bags collected for all levels
    void printStatus() const;
};

#endif //TRASH_TRACKER_H
