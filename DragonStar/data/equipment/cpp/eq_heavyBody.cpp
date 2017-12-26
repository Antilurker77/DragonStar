// ==================================
//
// eq_heavyBody.cpp
//
// ==================================

#include "../header/eq_heavyBody.h"

Eq_IronArmor::Eq_IronArmor() {
	name = "Iron Armor";
	iconFilepath = "body.png";
	itemQuality = ItemQuality::COMMON;
	weight = 16;
	tier = 1;

	textureFilepath = "iron_armor.png";
	equipType = EquipType::HEAVY_BODY;
	equipmentID = EquipmentID::IRON_ARMOR;

	equipPower = 27;
	blockChance = 0.0;
	statMods = {};
}