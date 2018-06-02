// ==================================
//
// eq_medFeet.cpp
//
// ==================================

#include "../header/eq_medFeet.h"

#include "../../id/abilityID.h"
#include "../../id/auraID.h"
#include "../../id/category.h"
#include "../../id/element.h"
#include "../../id/equipmentID.h"
#include "../../id/equipType.h"
#include "../../id/itemQuality.h"
#include "../../id/statModType.h"

Eq_LeatherBoots::Eq_LeatherBoots() {
	name = "Leather Boots";
	iconFilepath = "feet.png";
	itemQuality = ItemQuality::Common;
	weight = 4;
	tier = 1;

	textureFilepath = "leather_boots.png";
	equipType = EquipType::MED_FEET;
	equipmentID = EquipmentID::LEATHER_BOOTS;

	equipPower = 4;
	blockChance = 0.0;
	statMods = {};
}