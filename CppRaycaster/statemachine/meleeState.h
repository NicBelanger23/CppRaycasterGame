#pragma once
#include "state.h"
class meleeState :
    public state
{
public:
    meleeState(int numConditions, std::string name, int minimumticks) : state(numConditions, name, minimumticks) {};   // Call the superclass constructor in the subclass' initialization list.
    
    void Tick(D2entity* entity) {
        //std::cout << "facing player - meleeState\n";
        entity->facePlayer();
        //std::cout << "getting closer to player - meleeState\n";
        entity->walkToPlayer();
        entity->melee();
    };
};

