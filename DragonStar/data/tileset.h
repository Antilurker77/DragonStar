// ==================================
//
// tileset.h
//
// Polymorphic class for tileset
// data.
//
// ==================================

#pragma once

#include "../core/assetManager.h"
#include "tile.h"

#include <SFML/Graphics.hpp>

class Tileset {
public:
	Tileset();

	Tile GetTile(int tileType);
	sf::Texture* GetTexture();
protected:
	sf::Texture* texture;
	Tile tiles[16];
};