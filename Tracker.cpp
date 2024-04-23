//
// Created by Noah Klaus on 4/23/24.
//


// START - Imports
#include "Tracker.h" // Importing header
#include <iostream>
// STOP  - Imports

// START - Namespaces
using namespace std;
// STOP - Namespaces


Tracker::Tracker() {
    head = nullptr;
}

Tracker::~Tracker() {
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
}

void Tracker::append(int level, int bagsCollected) {
    Node* newNode = new Node;
    newNode->level = level;
    newNode->trashBags = bagsCollected;
    newNode->next = nullptr;

    if (head == nullptr) {
        head = newNode;
    } else {
        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }
}

void Tracker::printStatus() const {
    Node* current = head;
    while (current != nullptr) {
        std::cout << "Level " << current->level << ": " << current->trashBags << " trash bags collected" << std::endl;
        current = current->next;
    }
}