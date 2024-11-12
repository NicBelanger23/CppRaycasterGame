#pragma once
#include "state.h"
class retreatState :
    public state
{
public:
    retreatState(int numConditions, std::string name, int minimumticks) : state(numConditions, name, minimumticks) {};   // Call the superclass constructor in the subclass' initialization list.

    void Tick(D2entity* entity) {
        //  std::cout<<"Retreating\n";
        entity->faceAwayFromPlayer();
        entity->walkAwayFromPlayer();
    };
};

