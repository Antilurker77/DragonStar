// ==================================
//
// eq_ironSpear.cpp
//
// ==================================

#include "../header/eq_ironSpear.h"

Eq_IronSpear::Eq_IronSpear() {
	name = "Iron Spear";
	iconFilepath = "spear.png";
	itemQuality = ItemQuality::COMMON;
	weight = 10;
	tier = 1;

	textureFilepath = "iron_spear.png";
	equipType = EquipType::SPEAR;
	equipmentID = EquipmentID::IRON_SPEAR;

	equipPower = 48;
	attackSpeed = 250;
	attackRange = 1;
	attributeMultiplier = 1.75;
	attackElements = { Element::PHYSICAL };
	blockChance = 0.0;
	statMods = {};
}