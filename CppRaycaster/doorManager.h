#include "vector2.h"
#include "GameManager.h"
#include "Player.h"
#pragma once
class doorManager
{
public:
	bool open = false;
	bool unlocked = false;
	vector2 Position;
	int RequiredEnemy;
	float OpeningDistance;

	doorManager() {
		RequiredEnemy = -1;
		Position = vector2(0, 0);
		OpeningDistance = -1;
		open = false;
		unlocked = false;
	}

	doorManager(vector2 position, int requiredEnemy, float openingDistance) {
		RequiredEnemy = requiredEnemy;
		Position = position;
		OpeningDistance = openingDistance;
		open = false;
		unlocked = false;
	}

	void tick() {
		cout << GameManager::remainingEntities;
		if (!unlocked && GameManager::remainingEntities < RequiredEnemy) {
			unlocked = true;
			Map::Level[(int)Position.Y][(int)Position.X] = 4;
		}

		if (unlocked && !open && ((Position - Player::localPlayer.position).sqrmagnitude() < (OpeningDistance * OpeningDistance))) {
			open = true;
			Map::Level[(int)Position.Y][(int)Position.X] = 0;
		}

	}
};

