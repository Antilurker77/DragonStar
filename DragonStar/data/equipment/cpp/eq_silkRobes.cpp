// ==================================
//
// eq_silkRobes.cpp
//
// ==================================

#include "../header/eq_silkRobes.h"

Eq_SilkRobes::Eq_SilkRobes() {
	name = "Silk Robes";
	iconFilepath = "armor.png";
	itemQuality = ItemQuality::COMMON;
	weight = 4;
	tier = 1;

	textureFilepath = "silk.png";
	equipType = EquipType::LIGHT_BODY;
	equipmentID = EquipmentID::SILK_ROBES;

	equipPower = 6;
	blockChance = 0.0;
	statMods = {};
}