// ==================================
//
// mp_testMapXS.cpp
//
// ==================================

#include "../header/mp_testMapXS.h"

#include "../../id/tilesetID.h"
#include "../../../hex/hexMath.h"

Mp_TestMapXS::Mp_TestMapXS(){
	tileset = Factory::CreateTileset(TilesetID::TEST_TILESET);

	std::vector<sf::Vector3i> shape;

	shape = Hex::HexLine(sf::Vector3i(0, 0, 0), sf::Vector3i(6, -12, 6));
	addTiles(shape, 0);

	buildVertexArray();
}