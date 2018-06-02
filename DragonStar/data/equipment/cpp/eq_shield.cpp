// ==================================
//
// eq_shield.cpp
//
// ==================================

#include "../header/eq_shield.h"

#include "../../id/abilityID.h"
#include "../../id/auraID.h"
#include "../../id/category.h"
#include "../../id/element.h"
#include "../../id/equipmentID.h"
#include "../../id/equipType.h"
#include "../../id/itemQuality.h"
#include "../../id/statModType.h"

Eq_IronShield::Eq_IronShield() {
	name = "Iron Shield";
	iconFilepath = "shield.png";
	itemQuality = ItemQuality::Common;
	weight = 6;
	tier = 1;

	textureFilepath = "iron_shield.png";
	equipType = EquipType::SHIELD;
	equipmentID = EquipmentID::IRON_SHIELD;

	equipPower = 14;
	blockChance = 0.15;
	statMods = {};
}