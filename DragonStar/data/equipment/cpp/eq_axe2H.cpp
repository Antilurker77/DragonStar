// ==================================
//
// eq_axe2H.cpp
//
// ==================================

#include "../header/eq_axe2H.h"

#include "../../id/abilityID.h"
#include "../../id/auraID.h"
#include "../../id/category.h"
#include "../../id/element.h"
#include "../../id/equipmentID.h"
#include "../../id/equipType.h"
#include "../../id/itemQuality.h"
#include "../../id/statModType.h"

Eq_IronGreataxe::Eq_IronGreataxe() {
	name = "Iron Greataxe";
	iconFilepath = "axe.png";
	itemQuality = ItemQuality::Common;
	weight = 11;
	tier = 1;

	textureFilepath = "iron_greataxe.png";
	equipType = EquipType::Axe2H;
	equipmentID = EquipmentID::IronGreataxe;

	equipPower = 110;
	attackSpeed = 330;
	attackRange = 1;
	attributeMultiplier = 2.20;
	attackElements = { Element::Physical };
	blockChance = 0.0;
	statMods = {};
}