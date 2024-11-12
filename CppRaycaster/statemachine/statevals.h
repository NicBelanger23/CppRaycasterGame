#include <iostream>
#include "valCollection.h"
#pragma once
class statevals
{
public:
	// Declare the static member variable
	static statevals* Instance;

	valCollection* EMPTY = new valCollection(0);

	//define health values
	enum HEALTH { LOW_HEALTH, MEDIUM_HEALTH, FULL_HEALTH};
	enum MAGASIN { EMPTY_MAG, LOW_MAG, MEDIUM_MAG, FULL_MAG };
	enum DISTANCE { IMMEDIATE_DISTANCE , CLOSE_DISTANCE, MEDIUM_DISTANCE, LONG_DISTANCE };
	enum VISIBILITY { DEAD_ON, INFRONT, BESIDE, CORNER_VISION, BEHIND }; 
	// how well the entity sees the player ^^^^^^^^^^

	// Health options
	valCollection* maxHealth = new valCollection(1);
	valCollection* notMaxHealth = new valCollection(2);
	valCollection* notLowHealth = new valCollection(2);
	valCollection* lowHealth = new valCollection(1);

	// Magasin options
	valCollection* maxMagasin = new valCollection(1);
	valCollection* notMaxMagasin = new valCollection(2);
	valCollection* notLowMagasin = new valCollection(2);
	valCollection* lowMagasin = new valCollection(1);
	valCollection* emptyMagasin = new valCollection(1);
	
	// Distance options
	valCollection* farDistance = new valCollection(1);
	valCollection* notFarDistance = new valCollection(3);
	valCollection* midDist = new valCollection(1);
	valCollection* notCloseDistance = new valCollection(2);
	valCollection* closeDistance = new valCollection(2);
	valCollection* immediateDistance = new valCollection(1);

	// Visibility options
	valCollection* notVisible = new valCollection(1);
	valCollection* visible = new valCollection(4);
	valCollection* barelyVisible = new valCollection(2);
	valCollection* easilyVisible = new valCollection(2);

	// Constructor increments the instance count
	statevals() {
		// populating Health options 
		notMaxHealth->add(LOW_HEALTH)->add(MEDIUM_HEALTH);
		notLowHealth->add(FULL_HEALTH)->add(MEDIUM_HEALTH);
		maxHealth->add(FULL_HEALTH);
		lowHealth->add(LOW_HEALTH);

		// populating Magasin options 
		maxMagasin->add(FULL_MAG);
		notMaxMagasin->add(LOW_MAG)->add(MEDIUM_MAG);
		notLowMagasin->add(MEDIUM_MAG)->add(FULL_MAG);
		lowMagasin->add(LOW_MAG);
		emptyMagasin->add(EMPTY_MAG);

		// populating Distance options 
		farDistance->add(LONG_DISTANCE);
		notFarDistance->add(CLOSE_DISTANCE)->add(MEDIUM_DISTANCE)->add(IMMEDIATE_DISTANCE);
		midDist->add(MEDIUM_DISTANCE);
		notCloseDistance->add(MEDIUM_DISTANCE)->add(LONG_DISTANCE);
		closeDistance->add(CLOSE_DISTANCE)->add(IMMEDIATE_DISTANCE);
		immediateDistance->add(IMMEDIATE_DISTANCE);

		// populating Visibility options 
		notVisible->add(BEHIND);
		visible->add(CORNER_VISION)->add(BESIDE)->add(INFRONT)->add(DEAD_ON);
		barelyVisible->add(CORNER_VISION)->add(BESIDE);
		easilyVisible->add(INFRONT)->add(DEAD_ON);
	}
};