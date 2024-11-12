#include "D2entity.h"
#include "Player.h"
#include <cmath>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include "GameManager.h"
#include "vector2.h"
#include "NicRay.h"
#include <iostream>
#include <set>
#include "./statemachine/stateMachine.h"

#pragma once
using namespace std;

NicRay collisionRay = NicRay();

D2entity::D2entity(int id, vector2 position) {
	DistanceFromPlayer = 99999;
	ID = id;
	Position = position;

	Verticies[0][0] = -0.4f;
	Verticies[0][1] = 0;

	Verticies[1][0] = -0.4f;
	Verticies[1][1] = 1.4f;

	Verticies[2][0] = 0.4f;
	Verticies[2][1] = 0;

	Verticies[3][0] = 0.4f;
	Verticies[3][1] = 1.4f;

	Indicies[0] = 0;
	Indicies[1] = 1;
	Indicies[2] = 2;
	Indicies[3] = 1;
	Indicies[4] = 2;
	Indicies[5] = 3;

	AnglePlayer = 180;
	GameManager::entityMap.insert(this);
}

D2entity::~D2entity() {
	cout << "Deleteing entity";
	GameManager::entityMap.erase(this);
	delete myMachine;
}

void D2entity::CalcVertices(float* list) {
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

float D2entity::AngleToPlayer() {
	vector2 d = Position - Player::localPlayer.position;
	AnglePlayer = Player::localPlayer.forwardVector.signedAngle(d);
	return AnglePlayer;
}

float D2entity::DistFromPlayer() {
	DistanceFromPlayer = (Position - Player::localPlayer.position).magnitude();
	return DistanceFromPlayer;
}

void D2entity::GoTo(vector2 v) {
	Position.Copy(v);
}

void D2entity::Move(vector2 v) {
	float dist = collisionRay.CalculateLineEquation(Position, v.normalize(), 2);
	if ((dist) > 0.5f) {
		Position += v * DeltaTime * 0.5f;
	}

}

void D2entity::DoCollision() {
	for (auto it = GameManager::entityMap.begin(); it != GameManager::entityMap.end(); ++it) {
		D2entity* entity = *it; // Dereference the iterator to get the entity pointer
		if (entity != this) { // Check if the pointer is not null
			vector2 dir = Position - entity->Position;
			float dist = dir.sqrmagnitude();
			if (dist < 0.15f) {
				Move(dir.normalize() * DeltaTime * 10);
			}
		}
	}

	vector2 dir = Position - Player::localPlayer.position;
	float dist = dir.sqrmagnitude();
	if (dist < 0.15f) {
		Move(dir.normalize() * (DeltaTime / dir.sqrmagnitude()));
	}


}

void D2entity::Update(float deltaTime) {
	DoCollision();
	DistFromPlayer();
	AngleToPlayer();


	if (myMachine != NULL) {
		//calculate health enum
		float hpercent = Health / maxHealth;
		myMachine->Health = 2;
		if(hpercent < 0.8){ myMachine->Health = 1; }
		if(hpercent < 0.4) { myMachine->Health = 0; }

		//calculate distance enum
		myMachine->Distance = 3;
		if (DistanceFromPlayer < 1.5) { myMachine->Distance = 2; }
		if (DistanceFromPlayer < 0.8) { myMachine->Distance = 1; }
		if (DistanceFromPlayer < 0.2f){ myMachine->Distance = 0; }

		myMachine->Visibility = 4;
		myMachine->Magizine = 3;


		float dist = collisionRay.CalculateLineEquation(Position, Player::localPlayer.position - Position, 10);
		if (dist < DistanceFromPlayer) {
			myMachine->Visibility = 4;
		}
		else {
			myMachine->Visibility = 0;
		}

		//call the update
		myMachine->Tick();

	}
}