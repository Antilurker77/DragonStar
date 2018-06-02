// ==================================
//
// mp_fieldField.cpp
//
// ==================================

#include "../header/mp_fieldField.h"

#include "../../id/tilesetID.h"
#include "../../../hex/hexMath.h"

Mp_FieldField::Mp_FieldField() {
	tileset = Factory::CreateTileset(TilesetID::Field);

	std::vector<sf::Vector3i> shape;

	shape = Hex::FilledHexagon(sf::Vector3i(1, -1, 0), 2);
	addTiles(shape, 0);

	shape = Hex::HexLine(sf::Vector3i(-2, 2, 0), sf::Vector3i(1, 2, -3));
	addTiles(shape, 0);

	shape = Hex::HexLine(sf::Vector3i(2, 1, -3), sf::Vector3i(4, -1, -3));
	addTiles(shape, 0);

	shape = Hex::HexLine(sf::Vector3i(-2, 3, -1), sf::Vector3i(0, 3, -3));
	addTiles(shape, 0);

	shape = Hex::HexLine(sf::Vector3i(2, 2, -4), sf::Vector3i(4, 0, -4));
	addTiles(shape, 0);

	shape = Hex::HexLine(sf::Vector3i(4, -3, -1), sf::Vector3i(4, -5, 1));
	addTiles(shape, 0);

	shape = Hex::HexLine(sf::Vector3i(3, -4, 1), sf::Vector3i(0, -4, 4));
	addTiles(shape, 0);

	shape = Hex::HexLine(sf::Vector3i(3, -5, 2), sf::Vector3i(0, -5, 5));
	addTiles(shape, 0);

	shape = Hex::HexLine(sf::Vector3i(-2, -1, 3), sf::Vector3i(0, -3, 3));
	addTiles(shape, 0);

	shape = Hex::HexLine(sf::Vector3i(0, 4, -4), sf::Vector3i(-3, 4, -1));
	addTiles(shape, 4);

	shape = Hex::HexLine(sf::Vector3i(-3, 3, 0), sf::Vector3i(-3, 2, 1));
	addTiles(shape, 4);

	shape = Hex::HexLine(sf::Vector3i(-3, -1, 4), sf::Vector3i(-1, -3, 4));
	addTiles(shape, 4);

	shape = Hex::HexLine(sf::Vector3i(-1, -4, 5), sf::Vector3i(-1, -5, 6));
	addTiles(shape, 4);

	shape = Hex::HexLine(sf::Vector3i(-1, 5, -4), sf::Vector3i(-4, 5, -1));
	addTiles(shape, 0);

	shape = Hex::HexLine(sf::Vector3i(-2, 6, -4), sf::Vector3i(-4, 6, -2));
	addTiles(shape, 0);

	shape = Hex::HexLine(sf::Vector3i(-4, 4, 0), sf::Vector3i(-4, 3, 1));
	addTiles(shape, 0);

	shape = Hex::HexLine(sf::Vector3i(-5, 5, 0), sf::Vector3i(-5, 4, 1));
	addTiles(shape, 0);

	shape = Hex::HexLine(sf::Vector3i(-3, -2, 5), sf::Vector3i(-2, -3, 5));
	addTiles(shape, 0);

	shape = Hex::HexLine(sf::Vector3i(-3, -3, 6), sf::Vector3i(-2, -4, 6));
	addTiles(shape, 0);

	buildVertexArray();
}