#include "state.h";
#include "statevals.h"
#include "stateExit.h"
#include "../D2entity.h"
#include <iostream>
#pragma once
class stateMachine
{
public:
	D2entity* owner;

	stateMachine(D2entity* own) {
		owner = own;
	}


	int Health = 0;
	int Magizine = 0;
	int Distance = 0;
	int Visibility = 0;  //how far to the left/right the player is

	state* currentState;

	void Tick() {
		currentState = currentState->checkexits(owner, Health, Magizine, Distance, Visibility);
		currentState->totalticks++;
		currentState->Tick(owner);
	}

	void Tick(int amount) {
		for (int i = 0; i < amount; i++) {
			Tick();
		}
	}

	virtual void Construct() {
		std::cout << "empty state machine";
	};

};

