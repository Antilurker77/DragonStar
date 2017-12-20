// ==================================
//
// eq_lightHands.cpp
//
// ==================================

#include "../header/eq_lightHands.h"

Eq_SilkGloves::Eq_SilkGloves() {
	name = "Silk Gloves";
	iconFilepath = "hands.png";
	itemQuality = ItemQuality::COMMON;
	weight = 2;
	tier = 1;

	textureFilepath = "silk_gloves.png";
	equipType = EquipType::LIGHT_HANDS;
	equipmentID = EquipmentID::SILK_GLOVES;

	equipPower = 2;
	blockChance = 0.0;
	statMods = {};
}