#include "stdafx.h"
#include "MYSystems.h"

#include "MYComponents.h"
#include <ecstasy/core/Family.hpp>
#include "EntityAPI.h"
#include "Collision.h"

using namespace EntityAPI;

MYSystems::MYSystems()
{
}


MYSystems::~MYSystems()
{
}

MaterialSystem::MaterialSystem() :IteratingSystem(Family::all<MaterialComponent>().get())
{
	this->setProcessing(false);
}

void MaterialSystem::processEntity(Entity * entity, float deltaTime)
{
}


void EngineAPI::setUpEngine(Engine & engine)
{
	engine.emplaceSystem<MaterialSystem>();
	engine.emplaceSystem<ControllSystem>();
	engine.emplaceSystem<ProjectileSystem>();
	engine.emplaceSystem<EnemySystem>();
	engine.emplaceSystem<WeopenSystem>();

}

ControllSystem::ControllSystem() :IteratingSystem(Family::all<ControllComponent>().get())
{
}

void ControllSystem::processEntity(Entity * entity, float deltaTime)
{
	auto cc = entity->get<ControllComponent>();

	if (!cc->loaded) {

		cc->currentLoadTime += deltaTime;

		if (cc->currentLoadTime > cc->timeToLoad) {
			cc->loaded = true;
		}
	}
}

ProjectileSystem::ProjectileSystem() :IteratingSystem(Family::all<Projectile,MaterialComponent>().get())
{
}


/// WARNING: this  is definately n^2
void ProjectileSystem::processEntity(Entity * entity, float deltaTime)
{

	auto projectile = entity->get<Projectile>();
	auto materialComponent = entity->get<MaterialComponent>();

	float lx = getEntityX(entity) + projectile->direction.x * materialComponent->speed * deltaTime;
	float ly = getEntityY(entity) + projectile->direction.y * materialComponent->speed * deltaTime;

	setEntityPosition(entity, lx, ly);

	projectile->timer -= deltaTime;

	if (projectile->timer < 0) {
		this->getEngine()->removeEntity(entity);
	}


	auto list = getEngine()->getSystem<EnemySystem>()->getEntities();

	for (Entity * e : *list) {
		//e->get<MaterialComponent>()->sprite
		if (Collision::PixelPerfectTest(e->get<MaterialComponent>()->sprite, materialComponent->sprite)) {
			this->getEngine()->removeEntity(entity);
			
			damage(entity , e);

			if(isDead(e))
				this->getEngine()->removeEntity(e);
		}
	}




}

EnemySystem::EnemySystem() :IteratingSystem(Family::all<EnemyComponent, MaterialComponent>().get())
{

}

void EnemySystem::processEntity(Entity * entity, float deltaTime)
{

}

WeopenSystem::WeopenSystem() :IteratingSystem(Family::all<WeopenHolder, MaterialComponent>().get())
{

}

void WeopenSystem::processEntity(Entity * entity, float deltaTime)
{
	auto wh = entity->get<WeopenHolder>();
	auto mc = entity->get<MaterialComponent>();

	auto angle = atan2(wh->aimY - getEntityY(entity), wh->aimX - getEntityX(entity));

	angle = angle * (180 / PI);
	wh->weopenSprite.setPosition(getEntityCenter(entity));
	wh->weopenSprite.setRotation(angle);



}
