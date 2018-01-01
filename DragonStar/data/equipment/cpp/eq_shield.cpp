// ==================================
//
// eq_shield.cpp
//
// ==================================

#include "../header/eq_shield.h"

Eq_IronShield::Eq_IronShield() {
	name = "Iron Shield";
	iconFilepath = "shield.png";
	itemQuality = ItemQuality::COMMON;
	weight = 6;
	tier = 1;

	textureFilepath = "iron_shield.png";
	equipType = EquipType::SHIELD;
	equipmentID = EquipmentID::IRON_SHIELD;

	equipPower = 14;
	blockChance = 0.15;
	statMods = {};
}