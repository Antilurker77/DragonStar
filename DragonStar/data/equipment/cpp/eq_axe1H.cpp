// ==================================
//
// eq_axe1H.cpp
//
// ==================================

#include "../header/eq_axe1H.h"

Eq_IronAxe::Eq_IronAxe() {
	name = "Iron Axe";
	iconFilepath = "axe.png";
	itemQuality = ItemQuality::COMMON;
	weight = 6;
	tier = 1;

	textureFilepath = "iron_axe.png";
	equipType = EquipType::AXE_1H;
	equipmentID = EquipmentID::IRON_AXE;

	equipPower = 33;
	attackSpeed = 220;
	attackRange = 1;
	attributeMultiplier = 1.10;
	attackElements = { Element::PHYSICAL };
	blockChance = 0.0;
	statMods = {};
}