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

	equipPower = 35;
	attackSpeed = 300;
	attackRange = 1;
	attributeMultiplier = 1.75;
	attackElements = { Element::PHYSICAL };
	blockChance = 0.0;
	//statMods = {};

	// on-hit damage test
	statMods = {
		StatMod(StatModType::ON_HIT_DAMAGE, 22.0, {Element::LIGHTNING}, {Category::ATTACK, Category::DIRECT})
	};
}