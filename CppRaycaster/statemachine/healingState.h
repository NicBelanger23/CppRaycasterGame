#pragma once
#include "state.h"
class healingState :
    public state
{
public:
    healingState(int numConditions, std::string name, int minimumticks) : state(numConditions, name, minimumticks) {};   // Call the superclass constructor in the subclass' initialization list.

    void Tick(D2entity* entity) {
        //std::cout << "healing - healingState\n";
        entity->heal();
    };
};

