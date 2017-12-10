// ==================================
//
// tileset.cpp
//
// ==================================

#include "tileset.h"

Tileset::Tileset(){
	
}

Tile Tileset::GetTile(int tileType){
	return tiles[tileType];
}

sf::Texture* Tileset::GetTexture(){
	return texture;
}