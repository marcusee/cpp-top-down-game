#pragma once
#include <ecstasy/core/Entity.hpp>
#include <SFML/Graphics.hpp>
using namespace ecstasy;


class GameWorld;
class TileMap;

class GameWorldInput
{
public:

	bool mousePressed = false;
	GameWorldInput();


	void listhen(sf::Event & event , GameWorld& world);
	void listhenPoll( GameWorld& world);

	void controlEntity(TileMap& tilemap , Entity* e);


	~GameWorldInput();
};

