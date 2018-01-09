// ==================================
//
// mp_testArenaB.cpp
//
// ==================================

#include "../header/mp_testArenaB.h"

#include "../../../hex/hexMath.h"

Mp_TestArenaB::Mp_TestArenaB() {
	tileset = Factory::CreateTileset(TilesetID::TEST_TILESET);

	std::vector<sf::Vector3i> shape;

	// 0 grass
	// 4 wall

	shape = Hex::FilledHexagon(sf::Vector3i(0, 0, 0), 2);
	addTiles(shape, 0);

	shape = Hex::FilledHexagon(sf::Vector3i(0, -3, 3), 1);
	addTiles(shape, 0);

	shape = { 
		sf::Vector3i(-2, 0, 2),  
		sf::Vector3i(-2, 2, 0), 
		sf::Vector3i(0, 2, -2), 
		sf::Vector3i(2, 0, -2), 
		sf::Vector3i(2, -2, 0), 
	};
	addTiles(shape, 4);

	buildVertexArray();
}