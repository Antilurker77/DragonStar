// ==================================
//
// eq_mace1H.cpp
//
// ==================================

#include "../header/eq_mace1H.h"

Eq_IronMace::Eq_IronMace() {
	name = "Iron Mace";
	iconFilepath = "mace.png";
	itemQuality = ItemQuality::COMMON;
	weight = 7;
	tier = 1;

	textureFilepath = "iron_mace.png";
	equipType = EquipType::MACE_1H;
	equipmentID = EquipmentID::IRON_MACE;

	equipPower = 36;
	attackSpeed = 240;
	attackRange = 1;
	attributeMultiplier = 1.2;
	attackElements = { Element::PHYSICAL };
	blockChance = 0.0;
	statMods = {};
}