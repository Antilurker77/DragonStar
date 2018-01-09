// ==================================
//
// mp_fieldSewer.cpp
//
// ==================================

#include "../header/mp_fieldSewer.h"

#include "../../../hex/hexMath.h"

Mp_FieldSewer::Mp_FieldSewer() {
	tileset = Factory::CreateTileset(TilesetID::FIELD);

	std::vector<sf::Vector3i> shape;

	shape = Hex::FilledHexagon(sf::Vector3i(3, -6, 3), 2);
	addTiles(shape, 8);
	shape = Hex::FilledHexagon(sf::Vector3i(3, -6, 3), 1);
	addTiles(shape, 1);

	shape = Hex::FilledHexagon(sf::Vector3i(4, 0, -4), 2);
	addTiles(shape, 8);
	shape = Hex::FilledHexagon(sf::Vector3i(4, 0, -4), 1);
	addTiles(shape, 1);

	shape = Hex::FilledHexagon(sf::Vector3i(-4, 0, 4), 2);
	addTiles(shape, 8);
	shape = Hex::FilledHexagon(sf::Vector3i(-4, 0, 4), 1);
	addTiles(shape, 1);

	shape = Hex::FilledHexagon(sf::Vector3i(-3, 6, -3), 2);
	addTiles(shape, 8);
	shape = Hex::FilledHexagon(sf::Vector3i(-3, 6, -3), 1);
	addTiles(shape, 1);

	shape = Hex::HexLine(sf::Vector3i(3, -1, 2), sf::Vector3i(3, -4, 1));
	addTiles(shape, 1);
	shape = Hex::HexLine(sf::Vector3i(4, -2, -2), sf::Vector3i(4, -5, 1));
	addTiles(shape, 4);
	shape = Hex::HexLine(sf::Vector3i(5, -2, -3), sf::Vector3i(5, -6, 1));
	addTiles(shape, 1);

	shape = Hex::HexLine(sf::Vector3i(-2, -1, 3), sf::Vector3i(1, -4, 3));
	addTiles(shape, 1);
	shape = Hex::HexLine(sf::Vector3i(-2, -2, 4), sf::Vector3i(1, -5, 4));
	addTiles(shape, 4);
	shape = Hex::HexLine(sf::Vector3i(-3, -2, 5), sf::Vector3i(1, -6, 5));
	addTiles(shape, 1);

	shape = Hex::HexLine(sf::Vector3i(-5, 6, -1), sf::Vector3i(-5, 2, 3));
	addTiles(shape, 1);
	shape = Hex::HexLine(sf::Vector3i(-4, 5, -1), sf::Vector3i(-4, 2, 2));
	addTiles(shape, 4);
	shape = Hex::HexLine(sf::Vector3i(-3, 4, -1), sf::Vector3i(-3, 1, 2));
	addTiles(shape, 1);

	shape = Hex::HexLine(sf::Vector3i(-1, 6, -5), sf::Vector3i(3, 2, -5));
	addTiles(shape, 1);
	shape = Hex::HexLine(sf::Vector3i(-1, 5, -4), sf::Vector3i(2, 2, -4));
	addTiles(shape, 4);
	shape = Hex::HexLine(sf::Vector3i(-1, 4, -3), sf::Vector3i(2, 1, -3));
	addTiles(shape, 1);

	shape = Hex::HexLine(sf::Vector3i(2, -4, 2), sf::Vector3i(2, 0, -2));
	addTiles(shape, 8);
	shape = Hex::HexLine(sf::Vector3i(1, -3, 2), sf::Vector3i(-1, -1, 2));
	addTiles(shape, 8);
	shape = Hex::HexLine(sf::Vector3i(1, 1, -2), sf::Vector3i(-1, 3, -2));
	addTiles(shape, 8);
	shape = Hex::HexLine(sf::Vector3i(-2, 0, 2), sf::Vector3i(-2, 4, -2));
	addTiles(shape, 8);

	shape = Hex::HexLine(sf::Vector3i(1, -7, 6), sf::Vector3i(-6, 0, 6));
	addTiles(shape, 8);
	shape = Hex::HexLine(sf::Vector3i(-6, 1, -5), sf::Vector3i(-6, 7, -1));
	addTiles(shape, 8);
	shape = Hex::HexLine(sf::Vector3i(6, -7, 1), sf::Vector3i(6, 0, -6));
	addTiles(shape, 8);
	shape = Hex::HexLine(sf::Vector3i(5, 1, -6), sf::Vector3i(-1, 7, -6));
	addTiles(shape, 8);

	buildVertexArray();
}