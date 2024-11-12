#pragma once
#include "D2entity.h"
// Structure for a node in the linked list
class LinkedNode {
public:
    D2entity* data;
    LinkedNode* next;
    LinkedNode() {}

};