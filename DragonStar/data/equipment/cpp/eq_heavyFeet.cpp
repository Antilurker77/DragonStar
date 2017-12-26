// ==================================
//
// eq_heavyFeet.cpp
//
// ==================================

#include "../header/eq_heavyFeet.h"

Eq_IronGreaves::Eq_IronGreaves() {
	name = "Iron Greaves";
	iconFilepath = "feet.png";
	itemQuality = ItemQuality::COMMON;
	weight = 8;
	tier = 1;

	textureFilepath = "iron_greaves.png";
	equipType = EquipType::HEAVY_FEET;
	equipmentID = EquipmentID::IRON_GREAVES;

	equipPower = 6;
	blockChance = 0.0;
	statMods = {};
}