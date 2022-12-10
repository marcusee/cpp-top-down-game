#include "stdafx.h"
#include "TileMap.h"
#include "TextureBank.h"
#include "Json.h"
#include <fstream>
#include "Collision.h"

using namespace nlohmann;

void TileMap::load()
{
	width = 16;
	height = 16;
	tileWidth = 64;
	tileHeight = 64;

	for (int y = 0; y < width; y++) {
		for (int x = 0; x < height; x++) {
			Tile tile;
			tile.index = y * width + x;
			tile.mapX = x;
			tile.mapY = y;

			tile.base.setTexture(*TextureBank::getTexture("grass"));

			int worldPositionX = x * tileWidth;
			int worldPositionY = y * tileHeight;

			tile.base.setPosition(worldPositionX, worldPositionY);

			tileList.emplace_back(tile);
		}
	}
}

void TileMap::load(string filename)
{
	std::ifstream file(filename + ".json");

	if (!file) {
		cout << "cannot find file " << filename << endl;
		load();
		file.close();
		return;
	}

	json jj;

	try {
		file >> jj;
	}
	catch (int a) {
		cout << "json format wrong" << endl;
		return;

	}

	file.close();

	tileWidth = 64;
	tileHeight = 64;

	 width = jj["width"].get<int>();
	 height = jj["height"].get<int>();

	vector<int> list = jj["data"].get<vector<int>>();

	for (int y = 0; y < width; y++) {
		for (int x = 0; x < height; x++) {
			int index = y * width + x;

			int value = list[index];
			TileType type = static_cast<TileType>(value);

			Tile tile;
			tile.index = index;
			tile.mapX = x;
			tile.mapY = y;
			tile.type = type;

			string textureName = "grass";

			if (type == TileType::GRASS) {
				textureName = "grass";
			}
			else if (type == TileType::WATER) {
				textureName = "waternesw";
				tile.floor = false;
			}
			else if (type == TileType::CASTLE_WALL) {
				textureName = "castle_wall";
				tile.floor = false;
			}
			tile.base.setTexture(*TextureBank::getTexture(textureName));

			int worldPositionX = x * tileWidth;
			int worldPositionY = y * tileHeight;

			tile.base.setPosition(worldPositionX, worldPositionY);

			tileList.emplace_back(tile);

		}
	}
}

Tile * TileMap::getTile(const sf::Vector2f & position)
{
	return getTile( position.x,  position.y);
}

Tile * TileMap::getTile(int x, int y)
{

	if (x < 0 || x >= width || y < 0 || y >= height) return nullptr;
	return &tileList[getKey(x, y)];

}

Tile * TileMap::getTile(int index)
{
	if (index < 0 || index >= tileList.size()) return nullptr;
	return &tileList[index];
}

Tile * TileMap::getTileWorld(float worldX, float worldY)
{
	int x = worldX / tileWidth;
	int y = worldY / tileHeight;

	return getTile(x,y);
}

int TileMap::getKey(int x, int y)
{
	return y * width + x;
}

TileMap::TileMap()
{

}


TileMap::~TileMap()
{
}

string TMAP::transformTileType(TileType type)
{


	static unordered_map<TileType, string> mapper = {
		{TileType::GRASS , "grass"},
		{TileType::WATER , "water" },
		{ TileType::CASTLE_WALL , "castle_wall" },

	};

	return mapper[type];
}

void TMAP::draw(sf::RenderWindow & window, TileMap & tilemap)
{

	const float left = window.getView().getCenter().x - window.getView().getSize().x *0.5f ;
	const float top = window.getView().getCenter().y - window.getView().getSize().y * 0.5f ;
	const float screenWidth = left + window.getView().getSize().x + tilemap.tileWidth;
	const float screenHeight = top + window.getView().getSize().y + tilemap.tileHeight;

	for (float y = top ; y < screenHeight; y+= tilemap.tileHeight) {
		for (float x = left ; x < screenWidth ; x += tilemap.tileWidth) {
			auto tile = tilemap.getTileWorld(x, y);
			if (tile != nullptr) {
				window.draw(tile->base);
			}
		}
	}

}

void TMAP::resetH(TileMap & tilemap)
{
	for (Tile & t : tilemap.tileList) {
		t.F = 0;
		t.H = 0;
		t.G = 0;
		t.parentNode = nullptr;
	}
}

vector<Tile*> TMAP::getArround(TileMap & tilemap, sf::Vector2f worldPosition)
{
	const int cMapX = worldPosition.x / tilemap.tileWidth;
	const int cMapY = worldPosition.y / tilemap.tileHeight;

	vector<Tile*> list = {
		tilemap.getTile(cMapX , cMapY),
		tilemap.getTile(cMapX - 1 , cMapY),
		tilemap.getTile(cMapX + 1, cMapY),
		tilemap.getTile(cMapX , cMapY + 1),
		tilemap.getTile(cMapX , cMapY - 1),
		tilemap.getTile(cMapX + 1, cMapY + 1),
		tilemap.getTile(cMapX - 1, cMapY - 1),
		tilemap.getTile(cMapX + 1, cMapY - 1),
		tilemap.getTile(cMapX - 1, cMapY + 1),
	};

	return list;
}

bool TMAP::collided(TileMap & tilemap, sf::Sprite & sprite)
{
	auto surrounding = getArround(tilemap, sprite.getPosition());
	for (Tile* t : surrounding) {
		if (t != nullptr) {
			if (!t->floor && Collision::PixelPerfectTest(t->base, sprite)) {
				return true;
			}
		}
	}
	return false;
}

sf::Vector2f TMAP::getCenter(const Tile & tile)
{
	
	return { 
		tile.base.getPosition().x + tile.base.getTextureRect().width / 2 ,
		tile.base.getPosition().y + tile.base.getTextureRect().height / 2 
	};
}
