// ==================================
//
// mp_fieldSmallIsland.cpp
//
// ==================================

#include "../header/mp_fieldSmallIsland.h"

#include "../../../hex/hexMath.h"

Mp_FieldSmallIsland::Mp_FieldSmallIsland() {
	tileset = Factory::CreateTileset(TilesetID::FIELD);

	std::vector<sf::Vector3i> shape;

	shape = Hex::FilledHexagon(sf::Vector3i(0, 0, 0), 4);
	addTiles(shape, 0);

	shape = Hex::FilledHexagon(sf::Vector3i(0, 0, 0), 1);
	addTiles(shape, 1);

	shape = Hex::HexRing(sf::Vector3i(0, 0, 0), 5);
	addTiles(shape, 8);

	buildVertexArray();
}