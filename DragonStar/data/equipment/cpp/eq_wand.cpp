// ==================================
//
// eq_wand.cpp
//
// ==================================

#include "../header/eq_wand.h"

#include "../../id/abilityID.h"
#include "../../id/auraID.h"
#include "../../id/category.h"
#include "../../id/element.h"
#include "../../id/equipmentID.h"
#include "../../id/equipType.h"
#include "../../id/itemQuality.h"
#include "../../id/statModType.h"

Eq_WoodenWand::Eq_WoodenWand() {
	name = "Wooden Wand";
	iconFilepath = "wand.png";
	itemQuality = ItemQuality::Common;
	weight = 2;
	tier = 1;

	textureFilepath = "wooden_wand.png";
	equipType = EquipType::Wand;
	equipmentID = EquipmentID::WoodenWand;

	equipPower = 30;
	attackSpeed = 200;
	attackRange = 4;
	attributeMultiplier = 0.6;
	attackElements = { Element::Arcane };
	blockChance = 0.0;
	statMods = {};
}