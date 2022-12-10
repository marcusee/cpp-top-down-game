#pragma once
#include "GameWorld.h"

enum class AIState {
	IDLE,
	CHASING,
	ATTACKING,

};



struct EntityAI
{
	AIState state;

};

namespace AI {

	void updateEntity(Entity* entity, Entity* target, GameWorld& world);
	void idle(Entity* entity, Entity* target, GameWorld& world);
	void attackRange(Entity* entity, Entity* target, GameWorld& world);
	void chaseEntity(Entity* entity, Entity* target, GameWorld& world);
	
}