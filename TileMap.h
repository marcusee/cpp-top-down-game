#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;

enum class  TileType {
	GRASS, WATER ,CASTLE_WALL
};




struct Tile {

	Tile* parentNode;
	
	TileType type;

	bool floor = true;
	bool solid = false;
	
	sf::Sprite base;
	sf::Sprite feature;

	int index = -1;
	int mapX = -1;
	int mapY = -1;


	int H = 0;
	int F = 0;
	int G = 0;

};

class TileMap
{
public:
	vector<Tile> tileList;
	int width;
	int height;
	int tileWidth;
	int tileHeight;


	void load();
	void load(string filename);
	Tile* getTile(const sf::Vector2f& position);
	Tile* getTile(int x, int y);
	Tile* getTile(int index);
	Tile* getTileWorld(float worldX, float worldY);
	int getKey(int x, int y);

	TileMap();
	~TileMap();
};


namespace TMAP {

	string transformTileType(TileType type);
	void draw(sf::RenderWindow& window, TileMap & tilemap);
	void resetH(TileMap& tilemap);
	vector<Tile*> getArround(TileMap & tilemap ,sf::Vector2f worldPosition);
	bool collided(TileMap& tilemap, sf::Sprite& sprite);
	sf::Vector2f getCenter(const Tile& tile);
}