// ==================================
//
// eq_medBody.cpp
//
// ==================================

#include "../header/eq_medBody.h"

Eq_LeatherArmor::Eq_LeatherArmor() {
	name = "Leather Armor";
	iconFilepath = "body.png";
	itemQuality = ItemQuality::COMMON;
	weight = 8;
	tier = 1;

	textureFilepath = "leather_armor.png";
	equipType = EquipType::MED_BODY;
	equipmentID = EquipmentID::LEATHER_ARMOR;

	equipPower = 16;
	blockChance = 0.0;
	statMods = {};
}