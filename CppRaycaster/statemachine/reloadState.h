#pragma once
#include "state.h"
class reloadState :
    public state
{
public:
    reloadState(int numConditions, std::string name, int minimumticks) : state(numConditions, name, minimumticks) {};   // Call the superclass constructor in the subclass' initialization list.

    void Tick(D2entity* entity) {
        //std::cout << "reloading - reloadState\n";
        entity->reload();
    };
};

