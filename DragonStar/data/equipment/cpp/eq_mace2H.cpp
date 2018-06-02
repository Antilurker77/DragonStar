// ==================================
//
// eq_mace2H.cpp
//
// ==================================

#include "../header/eq_mace2H.h"

#include "../../id/abilityID.h"
#include "../../id/auraID.h"
#include "../../id/category.h"
#include "../../id/element.h"
#include "../../id/equipmentID.h"
#include "../../id/equipType.h"
#include "../../id/itemQuality.h"
#include "../../id/statModType.h"

Eq_IronGreatmace::Eq_IronGreatmace() {
	name = "Iron Greatmace";
	iconFilepath = "mace.png";
	itemQuality = ItemQuality::Common;
	weight = 13;
	tier = 1;

	textureFilepath = "iron_greatmace.png";
	equipType = EquipType::Mace2H;
	equipmentID = EquipmentID::IronGreatmace;

	equipPower = 120;
	attackSpeed = 360;
	attackRange = 1;
	attributeMultiplier = 2.4;
	attackElements = { Element::Physical };
	blockChance = 0.0;
	statMods = {};
}