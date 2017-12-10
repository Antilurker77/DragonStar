// ==================================
//
// tile.h
//
// Structure that defines the
// properties of a tile.
//
// ==================================

#pragma once

#include <string>

struct Tile {
	std::string Name = "Unknown Tile Type";
	
	// Multiplier applied to movement costs over this tile.
	double MoveMod = 1.00f;

	// Prevents the use of skills and spells while on this tile.
	bool IsDisabler = false;

	bool IsLava = false;

	// Determines whether tile blocks vision and projectiles.
	bool IsOpaque = false;

	bool IsPassible = true;
	bool IsWater = false;
	bool IsFlyable = true;
};