// ==================================
//
// map.h
//
// Polymorphic class that handles map
// data.
//
// ==================================

#pragma once

#include "tileset.h"
#include "../hex/hexMath.h"

#include <unordered_map>
#include <memory>

// Data containing a vector of tiles and their data.
class Map {
public:
	Map();
	void Draw(sf::RenderWindow& window);

	Tile GetTile(sf::Vector3i coords);
	Tile GetTile(int x, int y);
	Tile GetTile(int x, int y, int z);
	double DistanceHeuristic(sf::Vector3i start, sf::Vector3i end, bool positiveOffset = false);

	sf::Vector2f GetMapBounds();
protected:
	std::unique_ptr<Tileset> tileset;
	std::unordered_map<sf::Vector3i, int> tiles;
	sf::VertexArray tileVertex;

	void addTiles(std::vector<sf::Vector3i> shape, int tileType);
	void buildVertexArray();
};