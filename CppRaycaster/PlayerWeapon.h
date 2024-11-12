#pragma once
class PlayerWeapon
{
private:
	int reloadingTicks; //how long a reload takes
	int remainingTicks; //how much time on the current reload

	int firingTicks;
	int drawFiringTicks;
	int coolDownTicks;
	int drawCoolDownTicks;


public:
	bool isReloading;
	bool drawFiring;
	float maxAngle;
	float Damage;
	int maxAmmo;
	int currentAmmo;

	float AmmoPercentage() {
		return (float)currentAmmo / (float)maxAmmo;
	}

	void TriggerDown();

	void BeginReload() {
		if (isReloading){ return; }
		if (currentAmmo >= maxAmmo) { return; }
		isReloading = true;
		remainingTicks = reloadingTicks;

	};
	void EndReload() {
		isReloading = false;
		currentAmmo = maxAmmo;
	};

	void Tick() {
		if (coolDownTicks > 0) {
			coolDownTicks--;
			drawCoolDownTicks--;

			if (drawCoolDownTicks == 0) {
				drawFiring = false;
			}
		}
		if (remainingTicks > 0) {
			remainingTicks--;
			if (remainingTicks == 0) {
				EndReload();
			}
		}
	};

	PlayerWeapon(float angle, float damage, float magisineSize) {
		maxAngle = angle;
		Damage = damage;
		maxAmmo = magisineSize;
		currentAmmo = maxAmmo;
		reloadingTicks = 50;
		remainingTicks = 0;
		isReloading = false;
		drawFiring = false;

		firingTicks = 5;
		drawFiringTicks = 3;
		coolDownTicks = 0;
		drawCoolDownTicks = 0;
	}

};

