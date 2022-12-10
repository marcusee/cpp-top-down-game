#pragma once
#include <SFML/Graphics.hpp>
#include <ecstasy/core/Engine.hpp>

#include "GameWorldInput.h"
#include "TileMap.h"

#include "EntityBuilder.h"
#include "WindowControl.h"

using namespace ecstasy;

enum class WorldState {

	NORMAL , 
};

class GameWorld
{

public:

	sf::RenderWindow&		window;
	GameWorldInput			input;
	EntityBuilder			builder;
	WorldState				STATE;
	TileMap					tileMap;
	WindowControl			windowControl;
	Engine					engine;

	GameWorld(sf::RenderWindow & window);

	void load();

	void listhenInput(sf::Event& event);

	void update(float deltaTime);

	void draw();

	~GameWorld();
};

namespace WORLD {
	

	void generateEntity(Engine& engine,string filename, sf::Vector2f worldPosition);
	void generateEntity(GameWorld& world ,string filename ,int x , int y);
	const vector<Entity*> getHeroes(GameWorld& world);

}