#include "SimpleAI.h"
#include "D2Entity.h"


void SimpleAI::Update(float deltaTime) {
	float x = MyEntity->Position[0];
	float y = MyEntity->Position[1];

	float desiredx = PatrolPositions[currentPatrol * 2];
	float desiredy = PatrolPositions[(currentPatrol * 2) + 1];

	float dx = desiredx - x;
	float dy = desiredy - y;

	if (D2Entity::calculateHpy(dx, dy) < minNavDistance) {
		currentPatrol++;
	}
	if (currentPatrol >= (sizeof(PatrolPositions) / 8)) {
		currentPatrol = 0;
	}

	float fx = dx / D2Entity::calculateHpy(dx, dy);
	float fy = dy / D2Entity::calculateHpy(dx, dy);

	x += fx * deltaTime * 0.5;
	y += fy * deltaTime * 0.5;

	MyEntity->GoTo(x, y);


}

SimpleAI::SimpleAI(D2Entity* me) {
	MyEntity = me;
};