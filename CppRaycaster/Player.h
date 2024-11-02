#pragma once
class Player
{
	public:
		float position[3];
		float forwardAxis = 0;
		float rightAxis = 0;
		float rotation = 0;
		float forwardVector[2];
		void Tick();
		void init();
		static Player localPlayer;
	private:
		bool ValidateRays();
};

