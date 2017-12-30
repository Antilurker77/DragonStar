// ==================================
//
// eq_dagger.cpp
//
// ==================================

#include "../header/eq_dagger.h"

Eq_IronDagger::Eq_IronDagger() {
	name = "Iron Dagger";
	iconFilepath = "dagger.png";
	itemQuality = ItemQuality::COMMON;
	weight = 4;
	tier = 1;

	textureFilepath = "iron_dagger.png";
	equipType = EquipType::DAGGER;
	equipmentID = EquipmentID::IRON_DAGGER;

	equipPower = 35;
	attackSpeed = 140;
	attackRange = 1;
	attributeMultiplier = 0.7;
	attackElements = { Element::PHYSICAL };
	blockChance = 0.0;
	statMods = {};
}