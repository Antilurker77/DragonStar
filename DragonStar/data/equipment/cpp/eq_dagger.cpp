// ==================================
//
// eq_dagger.cpp
//
// ==================================

#include "../header/eq_dagger.h"

#include "../../id/abilityID.h"
#include "../../id/auraID.h"
#include "../../id/category.h"
#include "../../id/element.h"
#include "../../id/equipmentID.h"
#include "../../id/equipType.h"
#include "../../id/itemQuality.h"
#include "../../id/statModType.h"

Eq_IronDagger::Eq_IronDagger() {
	name = "Iron Dagger";
	iconFilepath = "dagger.png";
	itemQuality = ItemQuality::Common;
	weight = 4;
	tier = 1;

	textureFilepath = "iron_dagger.png";
	equipType = EquipType::DAGGER;
	equipmentID = EquipmentID::IRON_DAGGER;

	equipPower = 35;
	attackSpeed = 140;
	attackRange = 1;
	attributeMultiplier = 0.7;
	attackElements = { Element::PHYSICAL };
	blockChance = 0.0;
	statMods = {};
}