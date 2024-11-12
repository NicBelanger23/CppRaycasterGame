#include "Player.h"
#include <cmath>
#include "NicRay.h"
#include "PlayerWeapon.h"
#include <iostream>

PlayerWeapon shotgun = PlayerWeapon(0.2f, 1.0f, 15);
Player Player::localPlayer;

float deltaTime = 0.033f; 
void Player::init() {
	position.Copy(1.5f, 2.5f);
	currentWeapon = &shotgun;
	bobbingTicks = 0;
}

void Player::Reload() {
	currentWeapon->BeginReload();
}

NicRay WalkingRay = NicRay();
vector2 traveldir;

void Player::Tick() {
	//dont to gameloop if dead
	if (!Alive) { return; }
	
	//looking
	rotation += lookAxis * deltaTime;
	//moving
	vector2 movement = vector2(cos(rotation), sin(rotation));
	forwardVector.Copy(movement);
	movement *= forwardAxis;

	vector2 left = vector2(-sin(rotation), cos(rotation)) * rightAxis;

	if(forwardAxis < 0.0f) {
		
		traveldir = forwardVector * -1;
	}
	else {
		traveldir = forwardVector;
	}

	vector2 sumMove = movement + left;
	vector2 xmov = vector2(sumMove.X, 0.0f);
	vector2 ymov = vector2(-0.001f, sumMove.Y);

	float d1 = WalkingRay.CalculateLineEquation(position, xmov, 4);
	if (d1 < 0.2f) {
		sumMove -= (xmov * 1);
		if (d1 < 0.1f) {
			sumMove -= (xmov * 0.2f);
		}
	}
	float d2 = WalkingRay.CalculateLineEquation(position, ymov, 4);
	if (d2 < 0.2f) {
		sumMove -= (ymov * 1);
		if (d2 < 0.1f) {
			sumMove -= (ymov * 0.2f);
		}

	}
	sumMove = sumMove.normalize() * deltaTime;
	position += sumMove;

	if (pressingTrigger) {
		currentWeapon->TriggerDown();
	}

	currentWeapon->Tick();

	bobbingTicks += sumMove.sqrmagnitude() / (1 + abs(lookAxis / 2));

}

bool Player::ValidateRays() {
	return  WalkingRay.CalculateLineEquation(position, traveldir, 2) > 0.1f;
}

void Player::Damage(float amount) {
	Health -= amount;
	if (Health <= 0) {
		Alive = false;
	}
}
