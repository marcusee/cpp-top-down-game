#pragma once
#include <ecstasy/utils/ComponentFactory.hpp>
#include <ecstasy/utils/Blueprint.hpp>
#include <ecstasy/utils/EntityFactory.hpp>
#include <ecstasy/utils/BlueprintParser.hpp>
#include <ecstasy/core/Engine.hpp>
#include "MYComponents.h"
#include "TextureBank.h"
class GameWorld;

using namespace ecstasy;



class MaterialComponentFactory : public ComponentFactory {
public:
	MaterialComponentFactory() {};
	MaterialComponentFactory(const MaterialComponentFactory& orig) = delete;
	bool assemble(Entity *entity, ComponentBlueprint &blueprint) {


		auto mc = entity->emplace<MaterialComponent>();
		mc->name = blueprint.getString("name", "hank");
		mc->textureName = blueprint.getString("textureName", "hank");
		mc->speed = blueprint.getFloat("speed", 250);

		mc->sprite.setTexture(*TextureBank::getTexture(mc->textureName));
		mc->sprite.setPosition(blueprint.getFloat("posX" , 0), blueprint.getFloat("posY", 0));

		return true;
	}
};

class ControlComponentFactory : public ComponentFactory {
public:
	ControlComponentFactory() {};
	ControlComponentFactory(const ControlComponentFactory& orig) = delete;
	bool assemble(Entity *entity, ComponentBlueprint &blueprint) {


		auto cc = entity->emplace<ControllComponent>();
		cc->timeToLoad = blueprint.getFloat("timeToLoad", 3.0f);
		cc->currentLoadTime = cc->timeToLoad;
		cc->loaded = true;

		return true;
	}
};

class EnemyComponentFactory : public ComponentFactory {
public:
	EnemyComponentFactory() {};
	EnemyComponentFactory(const EnemyComponentFactory& orig) = delete;
	bool assemble(Entity *entity, ComponentBlueprint &blueprint) {

		auto ec = entity->emplace<EnemyComponent>();
		ec->enemyAItype = blueprint.getString("type", "dumb");


		return true;
	}
};



class ProjectileComponentFactory : public ComponentFactory {
public:
	ProjectileComponentFactory() {};
	ProjectileComponentFactory(const ProjectileComponentFactory& orig) = delete;
	bool assemble(Entity *entity, ComponentBlueprint &blueprint) {
		auto pc = entity->emplace<Projectile>();
		pc-> damage = blueprint.getInt("damage", 1);
		pc->timer  = blueprint.getFloat("speed", 120.0f * 5);

		return true;
	}
};

class HealthComponentFactory : public ComponentFactory {
public:
	HealthComponentFactory() {};
	HealthComponentFactory(const HealthComponentFactory& orig) = delete;
	bool assemble(Entity *entity, ComponentBlueprint &blueprint) {
		auto hc = entity->emplace<HealthComponent>();
		hc->currentHP = blueprint.getInt("currentHP", 3);
		hc->maxHP = blueprint.getInt("maxHP", 3);


		return true;
	}
};

class WeopenHolderComponentFactory : public ComponentFactory {
public:
	WeopenHolderComponentFactory() {};
	WeopenHolderComponentFactory(const WeopenHolderComponentFactory& orig) = delete;
	bool assemble(Entity *entity, ComponentBlueprint &blueprint) {
		auto wh = entity->emplace<WeopenHolder>();
		wh->weopenName = blueprint.getString("name", "rifle");
		wh->textureName = blueprint.getString("textureName", "rifle");

		wh->weopenSprite.setTexture(*TextureBank::getTexture(wh->textureName));

		wh->weopenSprite.setOrigin(wh->weopenSprite.getTextureRect().width / 3, wh->weopenSprite.getTextureRect().height / 2);

		return true;
	}
};


class EntityBuilder
{
public:

	EntityBuilder();

	void buildEntity(string filename = "hank");
	
	void configure(GameWorld & world);

	~EntityBuilder();
private:
	void storeBlue_print(std::shared_ptr<EntityFactory> factory, std::string type);

};

