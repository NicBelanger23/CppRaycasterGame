#include <iostream>
#pragma once
class D2entity
{
public:
	void setHealth(int healtValue) {};
	void nextPatroll() { std::cout << "FORCING NEXT PATROLL\n"; };  //force go to next patroll point (avoid direct calling if possible)
	void nextClosestPatroll() { std::cout << "FORCING CLOSEST PATROLL\n"; };  //force go to closest patroll point (prefered)
	void doPatroll() { std::cout << "GOING TWORDS CURRENT PATROLL\n"; };    //walk one step twords the next patroll point, if at the point, NextPatroll() is called.
	void facePlayer() { std::cout << "LOOKING TWORDS PLAYER\n"; };   //turn to look at the player
	void faceAwayFromPlayer() { std::cout << "LOOKING AWAY FROM PLAYER\n"; };   //turn to look at the player
	void reload() { std::cout << "RELOADING WEAPON\n"; };       //reloads gun if able
	void walkToPlayer() { std::cout << "WALKING TO PLAYER\n"; }; //walks in the directon of player
	void walkAwayFromPlayer() { std::cout << "WALKING AWAY FROM PLAYER\n"; }; //walks in the directon of player
	void heal() { std::cout << "HEALING\n"; }; //walks in the directon of player
	void fireWeapon() { std::cout << "FIRING WEAPON\n"; }; //shots the weapon if able
	void melee() { std::cout << "PUNCHING\n"; }; //punches if able
	void lookRandom() { std::cout << "LOOKING IN RANDOM DIRECTION\n"; }; //looks twords random direction
};

