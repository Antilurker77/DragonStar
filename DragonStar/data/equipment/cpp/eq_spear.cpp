// ==================================
//
// eq_spear.cpp
//
// ==================================

#include "../header/eq_spear.h"

#include "../../id/abilityID.h"
#include "../../id/auraID.h"
#include "../../id/category.h"
#include "../../id/element.h"
#include "../../id/equipmentID.h"
#include "../../id/equipType.h"
#include "../../id/itemQuality.h"
#include "../../id/statModType.h"

Eq_IronSpear::Eq_IronSpear() {
	name = "Iron Spear";
	iconFilepath = "spear.png";
	itemQuality = ItemQuality::COMMON;
	weight = 10;
	tier = 1;

	textureFilepath = "iron_spear.png";
	equipType = EquipType::SPEAR;
	equipmentID = EquipmentID::IRON_SPEAR;

	equipPower = 80;
	attackSpeed = 250;
	attackRange = 1;
	attributeMultiplier = 1.6;
	attackElements = { Element::PHYSICAL };
	blockChance = 0.0;
	statMods = {};
}