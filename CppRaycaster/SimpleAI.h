class D2Entity;

#pragma once
class SimpleAI
{

	
public:

	D2Entity* MyEntity;
	float PatrolPositions[10] = { 4.5, 2.2, 4.5, 8, 2.5, 5, 1.5, 3, 2.2, 2.2 };
	float RemainingDistance = 0;
	int currentPatrol = 0;
	float minNavDistance = 0.2;

	void Update(float deltaTime);

	SimpleAI(D2Entity* me);
};

