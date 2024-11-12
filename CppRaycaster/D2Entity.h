#include <map>
#include <iostream>
#include "vector2.h"
#include "Player.h"
#include "Map.h"
#pragma once

class stateMachine;
class D2entity
{
private:
	float DeltaTime = 0.033f;
	float AngleToPlayer();
	float DistFromPlayer();

	public:
		int ID;
		vector2 Position = vector2::zero();
		float Verticies[4][2];
		int Indicies[6];

		int currentPatroll = 0;
		float DistanceFromPlayer;
		float AnglePlayer;
		float Health = 0;
		float maxHealth = 0;

		void CalcVertices(float* list);

		void GoTo(vector2 v);
		void Move(vector2 v);

		void DoCollision();

		stateMachine* myMachine;
		void Update(float deltaTime);
		
		D2entity(int id, vector2 position);
		~D2entity();

		//force go to next patroll point (avoid direct calling if possible)
		void nextPatroll() { }; 

		//force go to closest patroll point (prefered)
		void nextClosestPatroll() {
			int closest;
			float dist = 999;

			for (int i = 0; i < Map::numPatrolls; i++) {
				float mag = (Map::patrollrout[i] - Position).sqrmagnitude();
				if (mag < dist) {
					closest = i;
					dist = mag;
				}
			}
			currentPatroll = closest;
			std::cout << "FORCING CLOSEST PATROLL\n";
		};  

		//walk one step twords the next patroll point, if at the point, NextPatroll() is called.
		void doPatroll() {
			if (Map::numPatrolls > 0) {
				vector2 dir = Map::patrollrout[currentPatroll] - Position;
				if (dir.sqrmagnitude() < 0.25f) {
					currentPatroll++;
					currentPatroll %= Map::numPatrolls;
				}
				Move(dir.normalize());
			}

		};    

		void facePlayer() { };   //turn to look at the player
		void faceAwayFromPlayer() { };   //turn to look at the player
		void reload() { std::cout << "RELOADING WEAPON\n"; };       //reloads gun if able

		//walks in the directon of player
		void walkToPlayer() {
			vector2 dir = Player::localPlayer.position - Position;
			Move(dir.normalize());		
		}; 

		//walks in the opposite directon of player
		void walkAwayFromPlayer() {
			vector2 dir = Position - Player::localPlayer.position;
			Move(dir.normalize());
			std::cout << "WALKING AWAY FROM PLAYER\n";

		}; 

		void heal() { Health += 1.0; }; //walks in the directon of player
		void fireWeapon() { Player::localPlayer.Damage(0.05f); }; //shots the weapon if able
		void melee() { std::cout << "PUNCHING\n"; }; //punches if able
		void lookRandom() { }; //looks twords random direction
		void setHealth(float h) { maxHealth = h;  Health = h; };

		void TakeDamage(float amount) {
			Health -= amount;
			std::cout << "owowowowowowowowowowow";
			if (Health <= 0) {
				delete this;
			}
		}
};

