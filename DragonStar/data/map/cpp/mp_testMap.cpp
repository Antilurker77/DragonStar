// ==================================
//
// mp_testMap.cpp
//
// ==================================

#include "../header/mp_testMap.h"

#include "../../id/tilesetID.h"
#include "../../../hex/hexMath.h"

Mp_TestMap::Mp_TestMap(){
	tileset = Factory::CreateTileset(TilesetID::TestTileset);

	std::vector<sf::Vector3i> shape;

	shape = Hex::FilledHexagon(sf::Vector3i(0, 0, 0), 2);
	addTiles(shape, 0);

	shape = Hex::FilledHexagon(sf::Vector3i(6, -8, 2), 3);
	addTiles(shape, 0);

	shape = Hex::FilledHexagon(sf::Vector3i(6, -8, 2), 1);
	addTiles(shape, 8);

	shape = Hex::FilledHexagon(sf::Vector3i(0, -12, 12), 1);
	addTiles(shape, 0);

	shape = Hex::HexLine(sf::Vector3i(3, -3, 0), sf::Vector3i(4, -4, 0));
	addTiles(shape, 0);

	shape = Hex::HexLine(sf::Vector3i(2, -3, 1), sf::Vector3i(3, -4, 1));
	addTiles(shape, 0);

	shape = Hex::HexLine(sf::Vector3i(0, -3, 3), sf::Vector3i(0, -10, 10));
	addTiles(shape, 0);

	shape = Hex::HexLine(sf::Vector3i(2, -12, 10), sf::Vector3i(4, -10, 6));
	addTiles(shape, 0);

	buildVertexArray();
}