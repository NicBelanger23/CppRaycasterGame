#include "D2Entity.h"
#include "Player.h"
#include <cmath>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include "SimpleAI.h"
#include "GameManager.h"
#include <iostream>
#include <set>

#pragma once
using namespace std;

D2Entity::D2Entity(int id) {
	DistanceFromPlayer = 99999;
	ID = id;
	Position[0] = 1.5;
	Position[1] = 2.9f;

	Verticies[0][0] = -0.4;
	Verticies[0][1] = 0;

	Verticies[1][0] = -0.4;
	Verticies[1][1] = 1.4;

	Verticies[2][0] = 0.4;
	Verticies[2][1] = 0;

	Verticies[3][0] = 0.4;
	Verticies[3][1] = 1.4;

	Indicies[0] = 0;
	Indicies[1] = 1;
	Indicies[2] = 2;
	Indicies[3] = 1;
	Indicies[4] = 2;
	Indicies[5] = 3;

	GameManager::entityMap.insert(this);

	AI = new SimpleAI(this);


}


float D2Entity::calculateHpy(float a, float b) {
	return powf((a * a) + (b * b), 0.5f);
}

float dot(float v1[], float v2[]) {
	return v1[0] * v2[0] + v1[1] * v2[1];
}

float cross(float v1[], float v2[]) {
	return v1[0] * v2[1] - v1[1] * v2[0];
}

float signedAngle(float v1[], float v2[]) {
	// atan2(sinTheta, cosTheta)
	float angle = atan2(cross(v1, v2), dot(v1, v2));
	return angle; // Angle is in radians
}

void D2Entity::CalcVertices(float* list) {
	float pos = -AngleToPlayer() * 2;
	float dist = DistFromPlayer();
	if (dist <= 0) {
		dist = -dist;
	}
	for (int i = 0; i < 6; i++)
	{
		list[i * 2] = (Verticies[Indicies[i]][0]/dist) + pos;
		list[(i * 2) + 1] = -(1/dist) + (Verticies[Indicies[i]][1]/dist);
	}
}

float D2Entity::AngleToPlayer() {
	float px = Player::localPlayer.forwardVector[0];
	float py = Player::localPlayer.forwardVector[1];

	float dx = Position[0] - Player::localPlayer.position[0];
	float dy = Position[1] - Player::localPlayer.position[1];;

	float* newarry = new float[2];
	newarry[0] = dx;
	newarry[1] = dy;
	//std::cout << dx << " " << dy << std::endl;

	float a = signedAngle(Player::localPlayer.forwardVector, newarry);

	delete[] newarry;
	return a;
}

float D2Entity::DistFromPlayer() {
	float dx = Position[0] - Player::localPlayer.position[0];
	float dy = Position[1] - Player::localPlayer.position[1];
	DistanceFromPlayer = calculateHpy(dx, dy);
	return DistanceFromPlayer;
}

void D2Entity::GoTo(float x, float y) {
	Position[0] = x;
	Position[1] = y;
}

void D2Entity::Move(float x, float y) {
	Position[0] += x;
	Position[1] += y;
}

void D2Entity::Update(float deltaTime) {
	AI -> Update(deltaTime * ID);
	DistFromPlayer();
}