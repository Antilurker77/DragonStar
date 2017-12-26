// ==================================
//
// eq_heavyHands.cpp
//
// ==================================

#include "../header/eq_heavyHands.h"

Eq_IronGauntlets::Eq_IronGauntlets() {
	name = "Iron Gauntlets";
	iconFilepath = "hands.png";
	itemQuality = ItemQuality::COMMON;
	weight = 8;
	tier = 1;

	textureFilepath = "iron_gauntlets.png";
	equipType = EquipType::HEAVY_HANDS;
	equipmentID = EquipmentID::IRON_GAUNTLETS;

	equipPower = 6;
	blockChance = 0.0;
	statMods = {};
}