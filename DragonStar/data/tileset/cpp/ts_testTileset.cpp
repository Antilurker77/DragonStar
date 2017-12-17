// ==================================
//
// testTileset.cpp
//
// ==================================

#include "../header/ts_testTileset.h"

Ts_TestTileset::Ts_TestTileset(){
	texture = assetManager.LoadTexture("gfx/dungeon/test_tileset.png");
	texture->setSmooth(true);

	tiles[0].Name = "Grass";
	tiles[0].MoveMod = 1.f;
	tiles[0].IsDisabler = false;
	tiles[0].IsLava = false;
	tiles[0].IsOpaque = false;
	tiles[0].IsPassible = true;
	tiles[0].IsWater = false;
	tiles[0].IsFlyable = true;

	tiles[4].Name = "Stone Wall";
	tiles[4].MoveMod = 1.f;
	tiles[4].IsDisabler = false;
	tiles[4].IsLava = false;
	tiles[4].IsOpaque = true;
	tiles[4].IsPassible = false;
	tiles[4].IsWater = false;
	tiles[4].IsFlyable = false;

	tiles[8].Name = "Shallow Water";
	tiles[8].MoveMod = 2.f;
	tiles[8].IsDisabler = false;
	tiles[8].IsLava = false;
	tiles[8].IsOpaque = false;
	tiles[8].IsPassible = true;
	tiles[8].IsWater = true;
	tiles[8].IsFlyable = true;

	tiles[9].Name = "Deep Water";
	tiles[9].MoveMod = 1.f;
	tiles[9].IsDisabler = false;
	tiles[9].IsLava = false;
	tiles[9].IsOpaque = false;
	tiles[9].IsPassible = false;
	tiles[9].IsWater = true;
	tiles[9].IsFlyable = true;

	tiles[11].Name = "Lava";
	tiles[11].MoveMod = 1.f;
	tiles[11].IsDisabler = false;
	tiles[11].IsLava = true;
	tiles[11].IsOpaque = false;
	tiles[11].IsPassible = false;
	tiles[11].IsWater = false;
	tiles[11].IsFlyable = true;
}