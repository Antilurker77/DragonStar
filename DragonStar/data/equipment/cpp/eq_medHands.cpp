// ==================================
//
// eq_medHands.cpp
//
// ==================================

#include "../header/eq_medHands.h"

#include "../../id/abilityID.h"
#include "../../id/auraID.h"
#include "../../id/category.h"
#include "../../id/element.h"
#include "../../id/equipmentID.h"
#include "../../id/equipType.h"
#include "../../id/itemQuality.h"
#include "../../id/statModType.h"

Eq_LeatherGloves::Eq_LeatherGloves() {
	name = "Leather Gloves";
	iconFilepath = "hands.png";
	itemQuality = ItemQuality::Common;
	weight = 4;
	tier = 1;

	textureFilepath = "leather_gloves.png";
	equipType = EquipType::MedHands;
	equipmentID = EquipmentID::LeatherGloves;

	equipPower = 4;
	blockChance = 0.0;
	statMods = {};
}