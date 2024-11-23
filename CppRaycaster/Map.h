#include "vector2.h"

#pragma once
class Map
{
public:
	static int** Level;
	static vector2 LevelSize;
	static vector2 PlayerStartPosition;
	static float PlayerStartRotation;
	static vector2* patrollrout;
	static int numPatrolls;

	static void unloadLevel();
	static void loadLevelOne();
	static void loadLevelTwo(vector2 offset);
	static void loadLevelThree(vector2 offset);
};

