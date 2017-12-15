// ==================================
//
// map.cpp
//
// ==================================

#include "map.h"

Map::Map(){

}

// Renders the map to the screen.
void Map::Draw(sf::RenderWindow& window){
	window.draw(tileVertex, tileset->GetTexture());
}

// Gets the tile number for a single tile. Returns a "Void" tile if nothing in those coordinates is found.
Tile Map::GetTile(sf::Vector3i coords){
	auto it = tiles.find(coords);
	if (it == tiles.end()) {
		Tile t;
		t.Name = "Void";
		t.MoveMod = 1.00f;
		t.IsWater = false;
		t.IsOpaque = false;
		t.IsPassible = false;
		t.IsLava = false;
		t.IsDisabler = false;
		return t;
	}
	else {
		return tileset->GetTile(tiles.at(coords));
	}
}

// Gets the tile number for a single tile. Returns a "Void" tile if nothing in those coordinates is found.
Tile Map::GetTile(int x, int y, int z){
	return GetTile(sf::Vector3i(x, y, z));
}

// Gets the tile number for a single tile. Returns a "Void" tile if nothing in those coordinates is found.
Tile Map::GetTile(int x, int z){
	return GetTile(sf::Vector3i(x, -x - z, z));
}

// Returns the distance between two hexes, including movement costs.
double Map::DistanceHeuristic(sf::Vector3i start, sf::Vector3i end, bool positiveOffset){
	double distance = 0.0;

	std::vector<sf::Vector3i> line = Hex::HexLine(start, end, positiveOffset);
	for (int i = 1; i < line.size(); i++){
		distance += GetTile(line[i].x, line[i].z).MoveMod;
	}

	return distance;
}

// Adds the tiles to the map. Used for map construction.
void Map::addTiles(std::vector<sf::Vector3i> shape, int tileType){
	for (sf::Vector3i tile : shape){
		tiles[sf::Vector3i(tile.x, tile.y, tile.z)] = tileType;
	}
}

// Builds the vertex array. Call when finishing adding tiles.
void Map::buildVertexArray(){
	// intialize vertex array
	tileVertex.setPrimitiveType(sf::Quads);
	tileVertex.resize(tiles.size() * 4);

	int hexWidth = 64;
	int hexHeight = 56;

	int tileSize = 64;

	int i = 0;

	// assign cords and texture to each tile
	for (const auto &tile : tiles){
		int tileNumber = tile.second;
		int texX = (tileNumber % 4) * tileSize;
		int texY = (tileNumber / 4) * tileSize;


		sf::Vertex* quad = &tileVertex[i * 4];

		int col = tile.first.x;
		int row = tile.first.z;

		int posX = col * (hexWidth * 3 / 4) - (hexWidth / 2) - (tileSize - hexWidth) / 2;
		int posY = row * hexHeight + col * (hexHeight / 2) - (hexHeight / 2) - (tileSize - hexHeight) / 2;

		// quad cords
		// 0  1
		// 3  2
		quad[0].position = sf::Vector2f(posX, posY);
		quad[1].position = sf::Vector2f(posX + tileSize, posY);
		quad[2].position = sf::Vector2f(posX + tileSize, posY + tileSize);
		quad[3].position = sf::Vector2f(posX, posY + tileSize);

		// quad texture cords
		// 0  1
		// 3  2
		quad[0].texCoords = sf::Vector2f(texX, texY);
		quad[1].texCoords = sf::Vector2f(texX + tileSize, texY);
		quad[2].texCoords = sf::Vector2f(texX + tileSize, texY + tileSize);
		quad[3].texCoords = sf::Vector2f(texX, texY + tileSize);

		i++;
	}
}
