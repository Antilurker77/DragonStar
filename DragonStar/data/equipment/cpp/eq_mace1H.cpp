// ==================================
//
// eq_mace1H.cpp
//
// ==================================

#include "../header/eq_mace1H.h"

#include "../../id/abilityID.h"
#include "../../id/auraID.h"
#include "../../id/category.h"
#include "../../id/element.h"
#include "../../id/equipmentID.h"
#include "../../id/equipType.h"
#include "../../id/itemQuality.h"
#include "../../id/statModType.h"

Eq_IronMace::Eq_IronMace() {
	name = "Iron Mace";
	iconFilepath = "mace.png";
	itemQuality = ItemQuality::COMMON;
	weight = 7;
	tier = 1;

	textureFilepath = "iron_mace.png";
	equipType = EquipType::MACE_1H;
	equipmentID = EquipmentID::IRON_MACE;

	equipPower = 60;
	attackSpeed = 240;
	attackRange = 1;
	attributeMultiplier = 1.2;
	attackElements = { Element::PHYSICAL };
	blockChance = 0.0;
	statMods = {};
}