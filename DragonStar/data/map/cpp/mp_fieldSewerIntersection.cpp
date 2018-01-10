// ==================================
//
// mp_fieldSewerIntersection.cpp
//
// ==================================

#include "../header/mp_fieldSewerIntersection.h"

#include "../../id/tilesetID.h"
#include "../../../hex/hexMath.h"

Mp_FieldSewerIntersection::Mp_FieldSewerIntersection() {
	tileset = Factory::CreateTileset(TilesetID::FIELD);

	std::vector<sf::Vector3i> shape;

	shape = Hex::HexRing(sf::Vector3i(0, 0, 0), 4);
	addTiles(shape, 4);
	shape = Hex::FilledHexagon(sf::Vector3i(0, 0, 0), 3);
	addTiles(shape, 1);

	shape = Hex::HexLine(sf::Vector3i(-2, 5, -3), sf::Vector3i(-2, 9, -7));
	addTiles(shape, 8);
	shape = Hex::HexLine(sf::Vector3i(-1, 5, -4), sf::Vector3i(-1, 8, -7));
	addTiles(shape, 5);
	shape = Hex::HexLine(sf::Vector3i(0, 5, -5), sf::Vector3i(0, 8, -8));
	addTiles(shape, 5);
	shape = Hex::HexLine(sf::Vector3i(1, 4, -5), sf::Vector3i(1, 7, -8));
	addTiles(shape, 5);
	shape = Hex::HexLine(sf::Vector3i(2, 3, -5), sf::Vector3i(2, 7, -9));
	addTiles(shape, 8);

	shape = Hex::HexLine(sf::Vector3i(3, 2, -5), sf::Vector3i(7, 2, -9));
	addTiles(shape, 8);
	shape = Hex::HexLine(sf::Vector3i(4, 1, -5), sf::Vector3i(7, 1, -8));
	addTiles(shape, 5);
	shape = Hex::HexLine(sf::Vector3i(5, 0, -5), sf::Vector3i(8, 0, -8));
	addTiles(shape, 5);
	shape = Hex::HexLine(sf::Vector3i(5, -1, -4), sf::Vector3i(8, -1, -7));
	addTiles(shape, 5);
	shape = Hex::HexLine(sf::Vector3i(5, -2, -3), sf::Vector3i(9, -2, -7));
	addTiles(shape, 8);

	shape = Hex::HexLine(sf::Vector3i(5, -3, -2), sf::Vector3i(9, -7, -2));
	addTiles(shape, 8);
	shape = Hex::HexLine(sf::Vector3i(5, -4, -1), sf::Vector3i(8, -7, -1));
	addTiles(shape, 5);
	shape = Hex::HexLine(sf::Vector3i(5, -5, 0), sf::Vector3i(8, -8, 0));
	addTiles(shape, 5);
	shape = Hex::HexLine(sf::Vector3i(4, -5, 1), sf::Vector3i(7, -8, 1));
	addTiles(shape, 5);
	shape = Hex::HexLine(sf::Vector3i(3, -5, 2), sf::Vector3i(7, -9, 2));
	addTiles(shape, 8);

	shape = Hex::HexLine(sf::Vector3i(2, -5, 3), sf::Vector3i(2, -9, 7));
	addTiles(shape, 8);
	shape = Hex::HexLine(sf::Vector3i(1, -5, 4), sf::Vector3i(1, -8, 7));
	addTiles(shape, 5);
	shape = Hex::HexLine(sf::Vector3i(0, -5, 5), sf::Vector3i(0, -8, 8));
	addTiles(shape, 5);
	shape = Hex::HexLine(sf::Vector3i(-1, -4, 5), sf::Vector3i(-1, -7, 8));
	addTiles(shape, 5);
	shape = Hex::HexLine(sf::Vector3i(-2, -3, 5), sf::Vector3i(-2, -7, 9));
	addTiles(shape, 8);

	shape = Hex::HexLine(sf::Vector3i(-3, -2, 5), sf::Vector3i(-7, -2, 9));
	addTiles(shape, 8);
	shape = Hex::HexLine(sf::Vector3i(-4, -1, 5), sf::Vector3i(-7, -1, 8));
	addTiles(shape, 5);
	shape = Hex::HexLine(sf::Vector3i(-5, 0, 5), sf::Vector3i(-8, 0, 8));
	addTiles(shape, 5);
	shape = Hex::HexLine(sf::Vector3i(-5, 1, 4), sf::Vector3i(-8, 1, 7));
	addTiles(shape, 5);
	shape = Hex::HexLine(sf::Vector3i(-5, 2, 3), sf::Vector3i(-9, 2, 7));
	addTiles(shape, 8);

	shape = Hex::HexLine(sf::Vector3i(-5, 3, 2), sf::Vector3i(-9, 7, 2));
	addTiles(shape, 8);
	shape = Hex::HexLine(sf::Vector3i(-5, 4, 1), sf::Vector3i(-8, 7, 1));
	addTiles(shape, 5);
	shape = Hex::HexLine(sf::Vector3i(-5, 5, 0), sf::Vector3i(-8, 8, 0));
	addTiles(shape, 5);
	shape = Hex::HexLine(sf::Vector3i(-4, 5, -1), sf::Vector3i(-7, 8, -1));
	addTiles(shape, 5);
	shape = Hex::HexLine(sf::Vector3i(-3, 5, -2), sf::Vector3i(-7, 9, -2));
	addTiles(shape, 8);


	buildVertexArray();
}