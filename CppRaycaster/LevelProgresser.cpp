#include "LevelProgresser.h"
#include "Player.h"
#include "doorManager.h"
#include <iostream>
#include "Map.h"
int LevelProgresser::currentLevel = 0;
vector2 LevelProgresser::destination = vector2::one();
doorManager LevelProgresser::DM;
LevelProgresser::LevelProgresser() {}

void LevelProgresser::NextLevel(vector2 offset) {
	currentLevel++; 
	if (currentLevel == 1) { Map::loadLevelOne(); return; }
	if (currentLevel == 2) { Map::loadLevelTwo(offset); return; }
	if (currentLevel == 3) { Map::loadLevelThree(offset); return; }
}

void LevelProgresser::Tick() {	
	if ((Player::localPlayer.position - LevelProgresser::destination).sqrmagnitude() < 1) {
		NextLevel(Player::localPlayer.position - LevelProgresser::destination);
	}
	DM.tick();


}

