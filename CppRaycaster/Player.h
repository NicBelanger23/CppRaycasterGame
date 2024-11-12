#include "vector2.h"
#include "PlayerWeapon.h"
#pragma once
class Player
{
	public:
		//location
		vector2 position = vector2::zero();
		vector2 forwardVector;

		//events
		float forwardAxis = 0;
		float rightAxis = 0;
		float lookAxis = 0;
		float rotation = 0;
		bool pressingTrigger;

		//called every frame
		void Tick();
		//called at the start
		void init();
		//used for static refrences across the progeam
		static Player localPlayer;

		//interactions
		void Damage(float amount);
		float GetHealth() { return Health; };
		void Reload();
		PlayerWeapon* currentWeapon;

		//for viewBobbing
		float bobbingTicks;
	private:
		//for movement
		bool ValidateRays();
		float Health = 100;
		bool Alive = true;
};

