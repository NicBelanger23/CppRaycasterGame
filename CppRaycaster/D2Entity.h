#include "SimpleAI.h"
#include <map>


#pragma once
class D2Entity
{
	public:
		int ID;
		float Position[2];
		float Verticies[4][2];
		float DistanceFromPlayer;
		int Indicies[6];
		D2Entity(int id);
		void CalcVertices(float* list);

		float AngleToPlayer();
		float DistFromPlayer();
		void GoTo(float x, float y);
		void Move(float x, float y);

		SimpleAI* AI;
		void Update(float deltaTime);

		static float calculateHpy(float a, float b);
		
		
};

