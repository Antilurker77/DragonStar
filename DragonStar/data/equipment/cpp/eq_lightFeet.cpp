// ==================================
//
// eq_lightFeet.cpp
//
// ==================================

#include "../header/eq_lightFeet.h"

Eq_SilkShoes::Eq_SilkShoes() {
	name = "Silk Shoes";
	iconFilepath = "feet.png";
	itemQuality = ItemQuality::COMMON;
	weight = 2;
	tier = 1;

	textureFilepath = "silk_shoes.png";
	equipType = EquipType::LIGHT_FEET;
	equipmentID = EquipmentID::SILK_SHOES;

	equipPower = 2;
	blockChance = 0.0;
	statMods = {};
}