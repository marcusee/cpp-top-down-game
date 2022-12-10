#include "stdafx.h"
#include "EntityBuilder.h"

#include "GameWorld.h"

#include <iostream>
using namespace std;




EntityBuilder::EntityBuilder()
{
}

void EntityBuilder::buildEntity(string filename)
{

}

void EntityBuilder::configure(GameWorld & world)
{

	std::shared_ptr<EntityFactory> 	factory = std::make_shared<EntityFactory>();

	factory->addComponentFactory<MaterialComponentFactory>("Material");
	factory->addComponentFactory<ControlComponentFactory>("Controllable");
	factory->addComponentFactory<ProjectileComponentFactory>("Projectile");
	factory->addComponentFactory<EnemyComponentFactory>("Enemy");
	factory->addComponentFactory<HealthComponentFactory>("Health");
	factory->addComponentFactory<WeopenHolderComponentFactory>("WeopenHolder");

	world.engine.setEntityFactory(factory);

	storeBlue_print(factory, "hank");
	storeBlue_print(factory, "railBullet");
	storeBlue_print(factory, "chicken");
	storeBlue_print(factory, "archer");

}


void EntityBuilder::storeBlue_print(std::shared_ptr<EntityFactory> factory, std::string type)
{
	std::shared_ptr<EntityBlueprint> entityBlueprint;
	std::string error = parseBlueprint("blueprints/" + type + ".def", entityBlueprint);
	factory->addEntityBlueprint(type, entityBlueprint);
}

EntityBuilder::~EntityBuilder()
{
}
