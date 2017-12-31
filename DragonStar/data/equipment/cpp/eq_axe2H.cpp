// ==================================
//
// eq_axe2H.cpp
//
// ==================================

#include "../header/eq_axe2H.h"

Eq_IronGreataxe::Eq_IronGreataxe() {
	name = "Iron Greataxe";
	iconFilepath = "axe.png";
	itemQuality = ItemQuality::COMMON;
	weight = 11;
	tier = 1;

	textureFilepath = "iron_greataxe.png";
	equipType = EquipType::AXE_2H;
	equipmentID = EquipmentID::IRON_GREATAXE;

	equipPower = 110;
	attackSpeed = 330;
	attackRange = 1;
	attributeMultiplier = 2.20;
	attackElements = { Element::PHYSICAL };
	blockChance = 0.0;
	statMods = {};
}