// ==================================
//
// mp_testMapXL.cpp
//
// ==================================

#include "../header/mp_testMapXL.h"

#include "../../../hex/hexMath.h"

Mp_TestMapXL::Mp_TestMapXL(){
	tileset = Factory::CreateTileset(TilesetID::TEST_TILESET);

	std::vector<sf::Vector3i> shape;

	shape = Hex::FilledHexagon(sf::Vector3i(0, 0, 0), 200);
	addTiles(shape, 0);

	shape = Hex::FilledHexagon(sf::Vector3i(30, 0, -30), 20);
	addTiles(shape, 8);

	shape = Hex::FilledHexagon(sf::Vector3i(100, -10, -90), 20);
	addTiles(shape, 8);

	buildVertexArray();
}