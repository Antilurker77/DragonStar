// ==================================
//
// eq_medFeet.cpp
//
// ==================================

#include "../header/eq_medFeet.h"

Eq_LeatherBoots::Eq_LeatherBoots() {
	name = "Leather Boots";
	iconFilepath = "feet.png";
	itemQuality = ItemQuality::COMMON;
	weight = 4;
	tier = 1;

	textureFilepath = "leather_boots.png";
	equipType = EquipType::MED_FEET;
	equipmentID = EquipmentID::LEATHER_BOOTS;

	equipPower = 4;
	blockChance = 0.0;
	statMods = {};
}