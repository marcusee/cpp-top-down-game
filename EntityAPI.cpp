#include "stdafx.h"
#include "EntityAPI.h"
#include "vector2.h"

void EntityAPI::fireProjectile(GameWorld & world, Entity * entity, string bulletName, sf::Vector2f worldPosition)
{

	auto bullet = world.engine.assembleEntity(bulletName);

	auto projectile = bullet->get<Projectile>();


	setEntityPosition(bullet, getEntityX(entity), getEntityY(entity));

	projectile->end = { worldPosition.x , worldPosition.y };

	projectile->start = {getEntityCenter(entity).x, getEntityCenter(entity).y};

	//projectile->distance = VECTOR2(projectile->start - projectile->end).mag() ;

	projectile->direction = VECTOR2(projectile->end - projectile->start).norm();
	
	projectile->state = projectile->moving;

	world.engine.addEntity(bullet);

}

void EntityAPI::damage(Entity * damager, Entity * target)
{


	if (damager->has<Projectile>() && target->has<HealthComponent>()) {

		target->get<HealthComponent>()->currentHP -= damager->get<Projectile>()->damage;

	}

}

bool EntityAPI::isDead(Entity * entity)
{
	if (entity->has<HealthComponent>()) {
		return entity->get<HealthComponent>()->currentHP <= 0;
	}
	else
		return false;
}


float EntityAPI::getEntityX(Entity * e)
{
	return getEntityPosition(e).x;
}

float EntityAPI::getEntityY(Entity * e)
{
	return getEntityPosition(e).y;
}

sf::Vector2f EntityAPI::getEntityPosition(Entity * e)
{
	return e->get<MaterialComponent>()->sprite.getPosition();
}

sf::Vector2f EntityAPI::getEntityCenter(Entity * e)
{
	const sf::Sprite & spr = e->get<MaterialComponent>()->sprite;

	return {
		spr.getPosition().x + spr.getTextureRect().width / 2 ,
		spr.getPosition().y + spr.getTextureRect().height / 2
	};

}


void EntityAPI::setEntityPosition(Entity * e, float x, float y) {
	e->get<MaterialComponent>()->sprite.setPosition(x, y);
}
