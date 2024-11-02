#pragma once
#include "D2Entity.h"
// Structure for a node in the linked list
class LinkedNode {
public:
    D2Entity* data;
    LinkedNode* next;
    LinkedNode() {}

};