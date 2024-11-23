#include "PlayerWeapon.h"
#include "GameManager.h"
#include "cmath"
using namespace std;

void PlayerWeapon::TriggerDown() {
    if (currentAmmo < 1) { return; } // dont shoot if no ammo
    if (coolDownTicks > 0) { return; } //dont shoot too quickly
    if (remainingTicks > 0) { return; } //dont shoot while reloading
    currentAmmo--;

    coolDownTicks = firingTicks;
    drawCoolDownTicks = drawFiringTicks;

    drawFiring = true;
    D2entity* closest = NULL;
    for (auto it = GameManager::entityMap.begin(); it != GameManager::entityMap.end(); ++it) {

        D2entity* entity = *it; // Dereference the iterator to get the entity pointer
        if (!entity) { // Check if the pointer is not null
            continue;
        }

        //is the enemy too far from the center of the screen
        if (abs(entity->AnglePlayer) > maxAngle) {
            continue;
        }
        //do we have a current closest
        if (!closest) {
            closest = entity;
            continue;
        }
        //if this enemy i
        if (entity->DistanceFromPlayer < closest->DistanceFromPlayer) {
            closest = entity;
        }


    }
    if (closest) {
        closest->TakeDamage(Damage);
    }

}


