#pragma once
#include "TileMap.h"

#include <vector>
#include <ecstasy/core/Entity.hpp>

using namespace std;
using namespace ecstasy;


namespace PathFinder {

	vector<sf::Vector2f> generatePath(TileMap& tilemap, Entity * entity, sf::Vector2f position);


};

