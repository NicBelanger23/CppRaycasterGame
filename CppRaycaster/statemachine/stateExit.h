#include "valCollection.h"
#pragma once
class state;
class stateExit
{
public:
	state* Destination;
	valCollection* Health;
	valCollection* Magazine;
	valCollection* Distance;
	valCollection* Visibility;
	bool requiresAll = false;

	//for actual implmentation
	stateExit(state* destination,
		valCollection* health,
		valCollection* magazine,
		valCollection* distance,
		valCollection* visibility,
		bool requiresall)
	{
		Destination = destination;
		Health = health;
		Magazine = magazine;
		Distance = distance;
		Visibility = visibility;
		requiresAll = requiresall;
	}

	bool evaluate(int health, int magazine, int distance, int visibility) {
		if (requiresAll) { return evaluateAND(health, magazine, distance, visibility); }
		return evaluateOR(health, magazine, distance, visibility);
	}

	bool evaluateOR(int health, int magazine, int distance, int visibility) {
		if (Health->contains(health, false)) {
			return true;
		}
		if (Magazine->contains(magazine, false)) {
			return true;
		}
		if (Distance->contains(distance, false)) {
			return true;
		}
		if (Visibility->contains(visibility, false)) {
			return true;
		}
		return false;
	}

	bool evaluateAND(int health, int magazine, int distance, int visibility) {
		if (!Health->contains(health, true)) {
			return false;
		}
		if (!Magazine->contains(magazine, true)) {
			return false;
		}
		if (!Distance->contains(distance, true)) {
			return false;
		}
		if (!Visibility->contains(visibility, true)) {
			return false;
		}
		return true;
	}
};

