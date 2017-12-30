// ==================================
//
// eq_sword2H.cpp
//
// ==================================

#include "../header/eq_sword2H.h"

Eq_IronGreatsword::Eq_IronGreatsword() {
	name = "Iron Greatsword";
	iconFilepath = "sword.png";
	itemQuality = ItemQuality::COMMON;
	weight = 9;
	tier = 1;

	textureFilepath = "iron_greatsword.png";
	equipType = EquipType::SWORD_2H;
	equipmentID = EquipmentID::IRON_GREATSWORD;

	equipPower = 100;
	attackSpeed = 300;
	attackRange = 1;
	attributeMultiplier = 2.00;
	attackElements = { Element::PHYSICAL };
	blockChance = 0.0;
	statMods = {};
}