// ==================================
//
// eq_heavyFeet.cpp
//
// ==================================

#include "../header/eq_heavyFeet.h"

#include "../../id/abilityID.h"
#include "../../id/auraID.h"
#include "../../id/category.h"
#include "../../id/element.h"
#include "../../id/equipmentID.h"
#include "../../id/equipType.h"
#include "../../id/itemQuality.h"
#include "../../id/statModType.h"

Eq_IronGreaves::Eq_IronGreaves() {
	name = "Iron Greaves";
	iconFilepath = "feet.png";
	itemQuality = ItemQuality::COMMON;
	weight = 8;
	tier = 1;

	textureFilepath = "iron_greaves.png";
	equipType = EquipType::HEAVY_FEET;
	equipmentID = EquipmentID::IRON_GREAVES;

	equipPower = 6;
	blockChance = 0.0;
	statMods = {};
}