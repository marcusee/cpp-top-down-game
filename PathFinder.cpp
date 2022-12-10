#include "stdafx.h"
#include "PathFinder.h"
#include "EntityAPI.h"

using namespace EntityAPI;

vector<sf::Vector2f> PathFinder::generatePath(TileMap & tilemap, Entity * entity, sf::Vector2f goal)
{
	std::vector<Tile*> openList;
	std::vector<Tile*> closedList;
	std::vector<Tile*> pathList;
	std::vector<sf::Vector2f> m_targetPositions;

	std::vector<Tile*>::iterator position;
	Tile* currentNode;

	// Reset all nodes.
	TMAP::resetH(tilemap);

		// Store the start and goal nodes.
	
	Tile* startNode = tilemap.getTile(getEntityPosition(entity));
	Tile* goalNode = tilemap.getTile(goal);

	// Check we have a valid path to find. If not we can just end the function as there's no path to find.
	if (startNode == goalNode)
	{
		// Clear the vector of target positions.
		m_targetPositions.clear();

		// Exit the function.
		return m_targetPositions;
	}

	// Pre-compute our H cost (estimated cost to goal) for each node.
	for (int i = 0; i < tilemap.width; i++)
	{
		for (int j = 0; j < tilemap.height ; j++)
		{
			int rowOffset, heightOffset;
			Tile* node = tilemap.getTile(i, j);

			heightOffset = abs(node->mapY - goalNode->mapY);
			rowOffset = abs(node->mapX - goalNode->mapX);

			node->H = heightOffset + rowOffset;
		}
	}

	// Add the start node to the open list.
	openList.push_back(startNode);

	// While we have values to check in the open list.
	while (!openList.empty())
	{
		// Find the node in the open list with the lowest F value and mark it as current.
		int lowestF = INT_MAX;

		for (Tile* tile : openList)
		{
			if (tile->F < lowestF)
			{
				lowestF = tile->F;
				currentNode = tile;
			}
		}

		// Remove the current node from the open list and add it to the closed list.
		position = std::find(openList.begin(), openList.end(), currentNode);

		if (position != openList.end())
			openList.erase(position);

		closedList.push_back(currentNode);

		// Find all valid adjacent nodes.
		std::vector<Tile*> adjacentTiles;
		Tile* node;

		// Top.
		node = tilemap.getTile(currentNode->mapX, currentNode->mapY - 1);
		if ((node != nullptr) && (node->floor))
		{
			adjacentTiles.push_back(tilemap.getTile(currentNode->mapX, currentNode->mapY - 1));
		}

		// Right.
		node = tilemap.getTile(currentNode->mapX + 1, currentNode->mapY);
		if ((node != nullptr) && (node->floor))
		{
			adjacentTiles.push_back(tilemap.getTile(currentNode->mapX + 1, currentNode->mapY));
		}

		// Bottom.
		node = tilemap.getTile(currentNode->mapX, currentNode->mapY + 1);
		if ((node != nullptr) && (node->floor))
		{
			adjacentTiles.push_back(tilemap.getTile(currentNode->mapX, currentNode->mapY + 1));
		}

		// Left.
		node = tilemap.getTile(currentNode->mapX - 1, currentNode->mapY);
		if ((node != nullptr) && (node->floor))
		{
			adjacentTiles.push_back(tilemap.getTile(currentNode->mapX - 1, currentNode->mapY));
		}

		// For all adjacent nodes.
		for (Tile* node : adjacentTiles)
		{
			// If the node is our goal node.
			if (node == goalNode)
			{
				// Parent the goal node to current.
				node->parentNode = currentNode;

				// Store the current path.
				while (node->parentNode != nullptr)
				{
					pathList.push_back(node);
					node = node->parentNode;
				}

				// Empty the open list and break out of our for loop.
				openList.clear();
				break;
			}
			else
			{
				// If the node is not in the closed list.
				position = std::find(closedList.begin(), closedList.end(), node);
				if (position == closedList.end())
				{
					// If the node is not in the open list.
					position = std::find(openList.begin(), openList.end(), node);
					if (position == openList.end())
					{
						// Add the node to the open list.
						openList.push_back(node);

						// Set the parent of the node to the current node.
						node->parentNode = currentNode;

						// Calculate G (total movement cost so far) cost.
						node->G = currentNode->G + 10;

						// Calculate the F (total movement cost + heuristic) cost.
						node->F = node->G + node->H;
					}
					else
					{
						// Check if this path is quicker that the other.
						int tempG = currentNode->G + 10;

						// Check if tempG is faster than the other. I.e, whether it's faster to go A->C->B that A->C.
						if (tempG < node->G)
						{
							// Re-parent node to this one.
							node->parentNode = currentNode;
						}
					}
				}
			}
		}
	}

	// Clear the vector of target positions.
	m_targetPositions.clear();

	// Store the node locations as the enemies target locations.
	for (Tile* tile : pathList)
	{
		m_targetPositions.push_back(TMAP::getCenter(*tile));
	}

	// Reverse the target position as we read them from goal to origin and we need them the other way around.
	std::reverse(m_targetPositions.begin(), m_targetPositions.end());

	return m_targetPositions;
}
