// ==================================
//
// eq_wand.cpp
//
// ==================================

#include "../header/eq_wand.h"

Eq_WoodenWand::Eq_WoodenWand() {
	name = "Wooden Wand";
	iconFilepath = "wand.png";
	itemQuality = ItemQuality::COMMON;
	weight = 2;
	tier = 1;

	textureFilepath = "wooden_wand.png";
	equipType = EquipType::WAND;
	equipmentID = EquipmentID::WOODEN_WAND;

	equipPower = 30;
	attackSpeed = 200;
	attackRange = 4;
	attributeMultiplier = 0.6;
	attackElements = { Element::ARCANE };
	blockChance = 0.0;
	statMods = {};
}