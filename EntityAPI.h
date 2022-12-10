#pragma once
#include "GameWorld.h"
#include <ecstasy/core/Entity.hpp>

using namespace ecstasy;


namespace EntityAPI {

	void fireProjectile(GameWorld& world, Entity* entity , string bulletName, sf::Vector2f worldPosition);

	void damage(Entity* damager, Entity * target);

	bool isDead( Entity * entity);

	float getEntityX(Entity * e);

	float getEntityY(Entity* e);

	sf::Vector2f getEntityPosition(Entity * e);
	sf::Vector2f getEntityCenter(Entity * e);

	void setEntityPosition(Entity * e, float x, float y);
}