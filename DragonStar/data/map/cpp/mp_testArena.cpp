// ==================================
//
// mp_testArena.cpp
//
// ==================================

#include "../header/mp_testArena.h"

#include "../../id/tilesetID.h"
#include "../../../hex/hexMath.h"

Mp_TestArena::Mp_TestArena() {
	tileset = Factory::CreateTileset(TilesetID::TestTileset);

	std::vector<sf::Vector3i> shape;

	shape = Hex::FilledHexagon(sf::Vector3i(0, 0, 0), 5);
	addTiles(shape, 4);

	shape = Hex::FilledHexagon(sf::Vector3i(0, 0, 0), 4);
	addTiles(shape, 0);

	shape = Hex::FilledHexagon(sf::Vector3i(0, -5, 5), 1);
	addTiles(shape, 0);

	shape = { sf::Vector3i(-2, 1, 1) };
	addTiles(shape, 4);

	shape = { sf::Vector3i(2, -1, -1) };
	addTiles(shape, 4);

	shape = { sf::Vector3i(0, -2, 2) };
	addTiles(shape, 4);

	shape = { sf::Vector3i(0, 2, -2) };
	addTiles(shape, 4);

	//shape = Hex::HexRing(sf::Vector3i(0, -5, 5), 2);
	//addTiles(shape, 9);

	buildVertexArray();
}