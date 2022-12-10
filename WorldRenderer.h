#pragma once
#include <SFML/Graphics.hpp>

#include <ecstasy/core/Engine.hpp>

using namespace ecstasy;
class WorldRenderer
{
public:
	WorldRenderer();
	~WorldRenderer();
};


namespace Renderer {

	void renderCursor(sf::RenderWindow & window , int type = 0);

	void drawMaterials(sf::RenderWindow & window, Engine& engine);
}