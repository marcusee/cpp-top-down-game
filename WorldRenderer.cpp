#include "stdafx.h"
#include "WorldRenderer.h"
#include "TextureBank.h"
#include "MYSystems.h"
#include "MYComponents.h"
#include <vector>

using namespace std;

WorldRenderer::WorldRenderer()
{
}


WorldRenderer::~WorldRenderer()
{
}

void Renderer::renderCursor(sf::RenderWindow & window, int type)
{
	sf::Vector2f worldPosition = window.mapPixelToCoords(sf::Mouse::getPosition(window), window.getView());
	sf::Sprite cursor;
	cursor.setTexture(*TextureBank::getTexture("square_highlight"));
	
	worldPosition.x -= cursor.getTextureRect().width * 0.5;
	worldPosition.y -= cursor.getTextureRect().height * 0.5;


	cursor.setPosition(worldPosition);

	

	window.draw(cursor);
}

void Renderer::drawMaterials(sf::RenderWindow & window, Engine & engine)
{
	const vector<Entity*> * list = engine.getSystem<MaterialSystem>()->getEntities();

	for (Entity* e : *list) {
		auto matComponent = e->get<MaterialComponent>();

		window.draw(matComponent->sprite);

		if (e->has<WeopenHolder>()) {
			window.draw(e->get<WeopenHolder>()->weopenSprite);
		}

	}

}
