#pragma once
#include "stateMachine.h"
#include "patrollState.h"
#include "meleeState.h"
#include "prefDistShootState.h"
#include "farDistShootState.h"
#include "retreatState.h"
#include "healingState.h"
#include "reloadState.h"
#include "../D2entity.h"

class soldier :
    public stateMachine
{
public:
	soldier(D2entity* own) : stateMachine(own) {};

	void Construct() {
		// current health
		owner->setHealth(20);
		std::cout << "soldier state machine\n";
		// 20 ticks per second
		 
		// STATES
					//last value is the minimum amount of ticks the state should latst
		state* patrolling = new patrollState(10, "patrol", 4);  //40 is prechosen

		state* prefDistShooting = new prefDistShootState(10,"shooting", 5);//20 is prechosen
		state* farDistShooting = new farDistShootState(10,"shooting & moving to the player", 5); //20 is prechosen
		state* meleeAttack = new meleeState(10, "melee", 2); //20 is prechosen

		state* retreating = new retreatState(10, "retreat", 5);//100 is prechosen
		state* healing = new healingState(10,"heal",5);//60 is prechosen
		state* reloading = new reloadState(10, "reloading", 2); //60 is prechosen

		statevals* v = statevals::Instance;
		
		// STATE EXITS AND CONDITIONS
		// EMPTY if doesnt matter
														//health	magasin		distance	visibility  OR(false)/AND(true)
		stateExit* goPatroll = new stateExit(patrolling, v->notLowHealth, v->notLowMagasin, v->notCloseDistance, v->notVisible, true);
		
		stateExit* goHit = new stateExit(meleeAttack, v->notLowHealth, v->EMPTY, v->immediateDistance, v->easilyVisible, true);
		stateExit* prefdshoot = new stateExit(prefDistShooting, v->notLowHealth, v->notLowMagasin, v->midDist, v->visible, true);
		stateExit* fardshoot = new stateExit(farDistShooting, v->notLowHealth, v->notLowMagasin, v->farDistance, v->visible, true);

		stateExit* goRetreat = new stateExit(retreating, v->lowHealth, v->lowMagasin, v->EMPTY, v->EMPTY, false);
		stateExit* goHeal = new stateExit(healing, v->lowHealth, v->EMPTY,v->notCloseDistance, v->notVisible, true );
		stateExit* goReload = new stateExit(reloading, v->notLowHealth, v->lowMagasin, v->notCloseDistance, v->EMPTY, true);

		// CONNECTING THE STATES

		patrolling->addExit(prefdshoot)->addExit(fardshoot)->addExit(goHit)->addExit(goRetreat)->addExit(goHeal)->addExit(goReload);
		
		prefDistShooting->addExit(goPatroll)->addExit(fardshoot)->addExit(goHit)->addExit(goReload)->addExit(goRetreat);
		farDistShooting->addExit(goPatroll)->addExit(prefdshoot)->addExit(goHit)->addExit(goReload)->addExit(goRetreat);
		meleeAttack->addExit(goPatroll)->addExit(prefdshoot)->addExit(fardshoot)->addExit(goRetreat);

		retreating->addExit(goHeal)->addExit(goReload)->addExit(goPatroll)->addExit(fardshoot)->addExit(prefdshoot)->addExit(goHit);
		healing->addExit(goPatroll)->addExit(fardshoot);
		reloading->addExit(prefdshoot)->addExit(fardshoot)->addExit(goHeal);

		currentState = patrolling;
		currentState->atTheStart(owner);
	};
};

