// ==================================
//
// eq_mace2H.cpp
//
// ==================================

#include "../header/eq_mace2H.h"

Eq_IronGreatmace::Eq_IronGreatmace() {
	name = "Iron Greatmace";
	iconFilepath = "mace.png";
	itemQuality = ItemQuality::COMMON;
	weight = 13;
	tier = 1;

	textureFilepath = "iron_greatmace.png";
	equipType = EquipType::MACE_2H;
	equipmentID = EquipmentID::IRON_GREATMACE;

	equipPower = 120;
	attackSpeed = 360;
	attackRange = 1;
	attributeMultiplier = 2.4;
	attackElements = { Element::PHYSICAL };
	blockChance = 0.0;
	statMods = {};
}