#include "vector2.h"
#pragma once
class Map
{
public:
	static int Level1[10][10];
	static int Level1Size[2];

	static vector2* patrollrout;
	static int numPatrolls;


	static void loadLevelOne();
};

