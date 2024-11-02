#include "Player.h"
#include <cmath>
#include "NicRay.h"
#include <iostream>
Player Player::localPlayer;
float deltaTime = 0.033f; 
void Player::init() {
	position[0] = 1.5f;
	position[1] = 2.5f;
}

NicRay WalkingRay = NicRay();
float travelrot;

void Player::Tick() {
	rotation += rightAxis * deltaTime;
	float x = cos(rotation);
	float y = sin(rotation);

	forwardVector[0] = x;
	forwardVector[1] = y;

	travelrot = rotation;

	if(forwardAxis < 0.0f) {
		
		travelrot += 180.0f;
	}

	if (ValidateRays()) {
		position[0] += forwardVector[0] * deltaTime * forwardAxis;
		position[1] += forwardVector[1] * deltaTime * forwardAxis;
	}


}

bool Player::ValidateRays() {
	return  WalkingRay.CalculateLineEquation(position, travelrot, 2) > 0.1f;
}
