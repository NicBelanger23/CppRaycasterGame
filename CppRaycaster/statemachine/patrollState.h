#pragma once
#include <iostream>
#include "state.h"
class patrollState :
    public state
{
public:
    patrollState(int numConditions, std::string name, int minimumticks) : state(numConditions, name, minimumticks) {};   // Call the superclass constructor in the subclass' initialization list.
    
    void Tick(D2entity* entity) {
        //std::cout << "patrolling - patrollState\n";
        entity->doPatroll();
    };

    void atTheStart(D2entity* entity) {
        entity->nextClosestPatroll();
    }
};

