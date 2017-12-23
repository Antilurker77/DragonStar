// ==================================
//
// eq_staff.cpp
//
// ==================================

#include "../header/eq_staff.h"

Eq_WoodenStaff::Eq_WoodenStaff() {
	name = "Wooden Staff";
	iconFilepath = "staff.png";
	itemQuality = ItemQuality::COMMON;
	weight = 7;
	tier = 1;

	textureFilepath = "wooden_staff.png";
	equipType = EquipType::STAFF;
	equipmentID = EquipmentID::WOODEN_STAFF;

	equipPower = 24;
	attackSpeed = 260;
	attackRange = 1;
	attributeMultiplier = 0.8;
	attackElements = { Element::PHYSICAL };
	blockChance = 0.0;
	statMods = {};
}