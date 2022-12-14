// SandGrouse2.cpp : Defines the entry point for the console application.
//
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include <SFML/Graphics.hpp>
#include "GameWorld.h"

static const sf::Time	TimePerFrame = sf::seconds(1.f / 60.f);;


int main()
{
	sf::RenderWindow window(sf::VideoMode(960, 640), "SandGrouse");
	window.setFramerateLimit(60);


	GameWorld world(window);
	world.load();
	float lastTime = 0;


	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (window.isOpen())
	{

		sf::Time dt = clock.restart();
		timeSinceLastUpdate += dt;


		sf::Event event;
		while (window.pollEvent(event))
		{

			world.listhenInput(event);

			if (event.type == sf::Event::Closed)
				window.close();
		
			
		}

		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			float deltaTime = TimePerFrame.asSeconds();
			world.update(deltaTime);
			window.clear();
			world.draw();
			window.display();
		}



	}

	return 0;
}