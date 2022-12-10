#include "stdafx.h"
#include "GameWorldInput.h"
#include "MYComponents.h"
#include <SFML/Graphics.hpp>
#include "EntityAPI.h"
#include <iostream>
using namespace std;
using namespace EntityAPI;

GameWorldInput::GameWorldInput(): mousePressed(false)
{
}


void GameWorldInput::listhen(sf::Event & event , GameWorld & world)
{
	/*
	if (event.type == sf::Event::MouseButtonPressed) {
		sf::Vector2f worldPosition = world.window.mapPixelToCoords(sf::Mouse::getPosition(world.window), world.window.getView());
		sf::Vector2f screenPosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(world.window));



		/// NOTE:(marcus) maybe change the name of lastMouseClicked;...
		if (event.mouseButton.button == sf::Mouse::Left) {
			const vector<Entity*> elist = WORLD::getHeroes(world);
			fireProjectile(world , elist.at(0), "railBullet" , worldPosition);

		}
	}
	*/
}

void GameWorldInput::listhenPoll( GameWorld & world)
{
	sf::Vector2f worldPosition = world.window.mapPixelToCoords(sf::Mouse::getPosition(world.window), world.window.getView());
	sf::Vector2f screenPosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(world.window));
	const vector<Entity*> elist = WORLD::getHeroes(world);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !mousePressed){


		if (elist.at(0)->get<ControllComponent>()->loaded) {


			fireProjectile(world, elist.at(0), "railBullet", worldPosition);
			mousePressed = true;
			elist.at(0)->get<ControllComponent>()->loaded = false;
			elist.at(0)->get<ControllComponent>()->currentLoadTime = 0;


		}

	}
	else if(!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		mousePressed = false;
	}

	if (elist.at(0)->has<WeopenHolder>()) {
		auto wh = elist.at(0)->get<WeopenHolder>();
		wh->aimX = worldPosition.x;
		wh->aimY = worldPosition.y;

	}
}

void GameWorldInput::controlEntity(TileMap& tilemap , Entity * e)
{
	float timeDelta = 1.0f / 60.0f;

	sf::Vector2f movementSpeed(0.f, 0.f);
	sf::Vector2f previousPosition = e->get<MaterialComponent>()->sprite.getPosition();
	auto material = e->get<MaterialComponent>();

	// Calculate where the current movement will put us.

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		// Set movement speed.
		movementSpeed.x = -material->speed * timeDelta;
	}
	else 	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))

	{
		// Set movement speed.
		movementSpeed.x = material->speed * timeDelta;
	}

	if  (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		// Set movement speed.
		movementSpeed.y = -material->speed * timeDelta;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		// Set movement speed.
		movementSpeed.y = material->speed * timeDelta;
	}
	
	sf::Vector2f newPosition;
	newPosition.x = previousPosition.x + movementSpeed.x;
	newPosition.y = previousPosition.y + movementSpeed.y;

	sf::Sprite newSprite = material->sprite;
	newSprite.setPosition(newPosition);

	if (!TMAP::collided(tilemap , newSprite)) {
		e->get<MaterialComponent>()->sprite.setPosition(newPosition);
	}

}


GameWorldInput::~GameWorldInput()
{
}
