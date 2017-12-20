// ==================================
//
// eq_lightHead.cpp
//
// ==================================

#include "../header/eq_lightHead.h"

Eq_SilkHat::Eq_SilkHat() {
	name = "Silk Hat";
	iconFilepath = "head.png";
	itemQuality = ItemQuality::COMMON;
	weight = 2;
	tier = 1;

	textureFilepath = "silk_hat.png";
	equipType = EquipType::LIGHT_HEAD;
	equipmentID = EquipmentID::SILK_HAT;

	equipPower = 3;
	blockChance = 0.0;
	statMods = {};
}