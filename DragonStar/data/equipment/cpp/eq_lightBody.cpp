// ==================================
//
// eq_lightBody.cpp
//
// ==================================

#include "../header/eq_lightBody.h"

Eq_SilkRobes::Eq_SilkRobes() {
	name = "Silk Robes";
	iconFilepath = "body.png";
	itemQuality = ItemQuality::COMMON;
	weight = 4;
	tier = 1;

	textureFilepath = "silk.png";
	equipType = EquipType::LIGHT_BODY;
	equipmentID = EquipmentID::SILK_ROBES;

	equipPower = 8;
	blockChance = 0.0;
	statMods = {};
}