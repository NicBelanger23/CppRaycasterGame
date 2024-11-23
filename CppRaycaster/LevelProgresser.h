#include "vector2.h"
#include "doorManager.h"
#pragma once
class LevelProgresser
{
public:
	static int currentLevel;
	static vector2 destination;
	static doorManager DM;
	LevelProgresser();
	void Tick();
	void NextLevel(vector2 offset);
};

