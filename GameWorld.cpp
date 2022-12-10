#include "stdafx.h"
#include "GameWorld.h"
#include "WorldRenderer.h"
#include "MYSystems.h"
#include <iostream>
GameWorld::GameWorld(sf::RenderWindow & window) : window(window) 
{
	tileMap.load("level1");

}

void GameWorld::load()
{


	EngineAPI::setUpEngine(engine);


	builder.configure(*this);

	auto e = engine.assembleEntity("hank");

	auto archer = engine.assembleEntity("archer");

	auto chicken = engine.assembleEntity("chicken");


	if (e == nullptr) {
		cout << "building entity failed" << endl;
		return;
	}
	engine.addEntity(e);
	engine.addEntity(chicken);
	engine.addEntity(archer);

	windowControl.lock(e);
}

void GameWorld::listhenInput(sf::Event & event)
{
	//input.listhen(event , *this);
}

void GameWorld::update(float deltaTime)
{

	input.listhenPoll(*this);

	const vector<Entity*> * list = engine.getSystem<ControllSystem>()->getEntities();
	const vector<Entity*> controllableEntities = *list;
	if (controllableEntities.size() > 0) {
		input.controlEntity(tileMap , controllableEntities.at(0));
	}


	windowControl.update(window);

	engine.update(deltaTime);

}

void GameWorld::draw()
{
	TMAP::draw(window, tileMap);
	//Renderer::renderCursor(window);
	Renderer::drawMaterials(window, engine);
}


GameWorld::~GameWorld()
{
	cout << "WORLD DESTROYED" << endl;
}



void WORLD::generateEntity(Engine & engine, string filename, sf::Vector2f worldPosition)
{
	auto e = engine.assembleEntity(filename);
	e->get<MaterialComponent>()->sprite.setPosition(worldPosition);
	engine.addEntity(e);
}

void WORLD::generateEntity(GameWorld & world, string filename, int x, int y)
{
	auto t = world.tileMap.getTile(x, y);
	auto p = t->base.getPosition();
	generateEntity(world.engine, filename, p);
}


const vector<Entity*> WORLD::getHeroes(GameWorld& world)
{

	return *world.engine.getSystem<ControllSystem>()->getEntities();
}
