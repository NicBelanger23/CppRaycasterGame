#pragma once
#include "state.h"
class farDistShootState :
    public state
{
public:
    farDistShootState(int numConditions, std::string name, int minimumticks) : state(numConditions, name, minimumticks) {};   // Call the superclass constructor in the subclass' initialization list.

    void Tick(D2entity* entity) {
        //std::cout << "shooting - farDistShootState\n";
        //std::cout << "facing player - farDistShootState\n";
        entity->facePlayer();
        //std::cout << "firing the weapon - farDistShootState\n";
        entity->fireWeapon();
        //std::cout << "getting closer - farDistShootState\n";
        entity->walkToPlayer();
    };
};

