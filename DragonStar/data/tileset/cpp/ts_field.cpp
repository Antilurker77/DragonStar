// ==================================
//
// ts_field.cpp
//
// ==================================

#include "../header/ts_field.h"

Ts_Field::Ts_Field() {
	texture = assetManager.LoadTexture("gfx/dungeon/field.png");

	// Grass
	tiles[0].Name = "Grass";
	tiles[0].MoveMod = 1.f;
	tiles[0].IsDisabler = false;
	tiles[0].IsLava = false;
	tiles[0].IsOpaque = false;
	tiles[0].IsPassible = true;
	tiles[0].IsWater = false;
	tiles[0].IsFlyable = true;

	// Stone Tiles
	tiles[1].Name = "Stone Tiles";
	tiles[1].MoveMod = 1.f;
	tiles[1].IsDisabler = false;
	tiles[1].IsLava = false;
	tiles[1].IsOpaque = false;
	tiles[1].IsPassible = true;
	tiles[1].IsWater = false;
	tiles[1].IsFlyable = true;

	// Shallow Water
	tiles[4].Name = "Shallow Water";
	tiles[4].MoveMod = 2.f;
	tiles[4].IsDisabler = false;
	tiles[4].IsLava = false;
	tiles[4].IsOpaque = false;
	tiles[4].IsPassible = true;
	tiles[4].IsWater = true;
	tiles[4].IsFlyable = true;

	// Deep Water
	tiles[5].Name = "Deep Water";
	tiles[5].MoveMod = 2.f;
	tiles[5].IsDisabler = false;
	tiles[5].IsLava = false;
	tiles[5].IsOpaque = false;
	tiles[5].IsPassible = false;
	tiles[5].IsWater = true;
	tiles[5].IsFlyable = true;

	// Stone Wall
	tiles[8].Name = "Stone Wall";
	tiles[8].MoveMod = 1.f;
	tiles[8].IsDisabler = false;
	tiles[8].IsLava = false;
	tiles[8].IsOpaque = true;
	tiles[8].IsPassible = false;
	tiles[8].IsWater = false;
	tiles[8].IsFlyable = false;
}