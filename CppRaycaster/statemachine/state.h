#include "stateExit.h"
#include <iostream>
#include "../D2entity.h"

#pragma once
class state
{
private:
	int size = 0;
	stateExit** exits; //an pointer to an array of pointers to exits
	std::string Name;
	int minimumTicks = 0;

public:
	int totalticks = 0;
	state(int numConditions, std::string name, int minimumticks) {
		exits = new stateExit * [numConditions];
		Name = name;
		minimumTicks = minimumticks;
	};
	state* addExit(stateExit* e) {
		exits[size] = e;
		size++;
		return this;
	};

	state* checkexits(D2entity* entity, int h, int m, int d, int v) {
		//if we have not been here for the minimum ticks, stay here
		if (totalticks < minimumTicks) { return this; }
		totalticks = 0; //reset the coutdown

		for (int i = 0; i < size; i++) {
			if (exits[i]->evaluate(h, m, d, v)) {
				state* d = exits[i]->Destination;
				atTheEnd(entity);
				d->atTheStart(entity);
				return d;
			}
		}
		return this;
	};

	virtual void atTheStart(D2entity* entity) {

	};

	virtual void Tick(D2entity* entity) {
		totalticks++;
		std::cout << Name << std::endl;
	};

	virtual void atTheEnd(D2entity* entity) {

	};
};

