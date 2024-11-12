#pragma once
#include "state.h"
class prefDistShootState :
    public state
{
public:
    prefDistShootState(int numConditions, std::string name, int minimumticks) : state(numConditions, name, minimumticks) {};   // Call the superclass constructor in the subclass' initialization list.
    
    void Tick(D2entity* entity) {
        //std::cout << "facing player - prefDistShootState\n";
        entity->facePlayer();
        //std::cout << "firing the weapon - prefDistShootState\n";
        entity->fireWeapon();
    };
};

