// ==================================
//
// eq_lightHands.cpp
//
// ==================================

#include "../header/eq_lightHands.h"

#include "../../id/abilityID.h"
#include "../../id/auraID.h"
#include "../../id/category.h"
#include "../../id/element.h"
#include "../../id/equipmentID.h"
#include "../../id/equipType.h"
#include "../../id/itemQuality.h"
#include "../../id/statModType.h"

Eq_SilkGloves::Eq_SilkGloves() {
	name = "Silk Gloves";
	iconFilepath = "hands.png";
	itemQuality = ItemQuality::Common;
	weight = 2;
	tier = 1;

	textureFilepath = "silk_gloves.png";
	equipType = EquipType::LIGHT_HANDS;
	equipmentID = EquipmentID::SILK_GLOVES;

	equipPower = 2;
	blockChance = 0.0;
	statMods = {};
}