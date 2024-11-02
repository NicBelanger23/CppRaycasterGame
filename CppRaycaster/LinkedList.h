#pragma once
#include <iostream>
#include "D2Entity.h"
#include "LinkedNode.h"
using namespace std;



// Define the linked list class
class LinkedList {
    // Pointer to the first node in the list


public:
    LinkedNode* head;
    // Constructor initializes head to NULL
    LinkedList() : head(NULL) {}

    // Function to Insert a new node at a specific position in the list
    void insertSorted(D2Entity* value) {

        // Initialize head if it's null
        if (!head) {
            head = new LinkedNode();
            head->data = value;
            return;
        }
        LinkedNode* newNode = new LinkedNode();
        newNode->data = value;
        if (value -> DistanceFromPlayer >= head->data->DistanceFromPlayer) {
            newNode->next = head;
            head = newNode;
            return;
        }

        if (!head->next) {
            head->next = newNode;
            return;
        }


        // Traverse to the node before the desired position
        LinkedNode* current = head->next;
        LinkedNode* prev = head;
        while (current) {
            if (value->DistanceFromPlayer >= current->data->DistanceFromPlayer) {
                prev->next = newNode;
                newNode->next = current;
                return;
            }
            prev = current;
            current = current->next;
        }
        prev->next = newNode;
    }

};
