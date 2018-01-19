// ==================================
//
// mp_fieldField.cpp
//
// ==================================

#include "../header/mp_fieldField.h"

#include "../../id/tilesetID.h"
#include "../../../hex/hexMath.h"

Mp_FieldField::Mp_FieldField() {
	tileset = Factory::CreateTileset(TilesetID::FIELD);

	std::vector<sf::Vector3i> shape;

	shape = Hex::FilledHexagon(sf::Vector3i(1, -1, 0), 2);
	addTiles(shape, 0);

	buildVertexArray();
}