// ==================================
//
// eq_medHands.cpp
//
// ==================================

#include "../header/eq_medHands.h"

Eq_LeatherGloves::Eq_LeatherGloves() {
	name = "Leather Gloves";
	iconFilepath = "hands.png";
	itemQuality = ItemQuality::COMMON;
	weight = 4;
	tier = 1;

	textureFilepath = "leather_gloves.png";
	equipType = EquipType::MED_HANDS;
	equipmentID = EquipmentID::LEATHER_GLOVES;

	equipPower = 4;
	blockChance = 0.0;
	statMods = {};
}