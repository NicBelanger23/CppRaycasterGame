#include "Player.h"
#include <iostream>
#pragma once
class EntityWeapon
{
public:
	int warmUpTime;  //how long to warm up
	int warmUpTicks; //current time warming up

	int roundTime; //how long a shot takes to fire
	int roundTicks; //how long the current shot has been

	int drawFiringTime; //how long a shot should be drawn as firing
	int drawFiringTicks; //how long the current shot has been drawn as firing
	bool drawFiring;

	int coolDownTime; //how long untill a warmup is needed again
	int coolDownTicks; //current time untill warmup is needed again

	EntityWeapon() {
		warmUpTime = 60;
		warmUpTicks = 0;

		roundTime = 10;
		roundTicks = 0;
		
		drawFiringTime = 3;
		drawFiringTicks = 0;
		drawFiring = false;

		coolDownTime = 10;
		coolDownTicks = 0;
	};

	void triggerDown() {

		coolDownTicks = coolDownTime;
		if (warmUpTicks < warmUpTime) { warmUpTicks++; return; }
		if (roundTicks > 0) { return; }
		
		//actually fire
		drawFiringTicks = drawFiringTime;
		roundTicks = roundTime;
		Player::localPlayer.Damage(1.0f);
	}

	void Tick() {
		roundTicks--;
		drawFiringTicks--;
		drawFiring = drawFiringTicks > 0;
		coolDownTicks--;
		
		if (coolDownTicks < 0) {
			warmUpTicks = 0;
			drawFiringTicks = 0;
			roundTicks = 0;
		}
	}
};

