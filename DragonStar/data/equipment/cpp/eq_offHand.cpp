// ==================================
//
// eq_offHand.cpp
//
// ==================================

#include "../header/eq_offHand.h"

#include "../../id/abilityID.h"
#include "../../id/auraID.h"
#include "../../id/category.h"
#include "../../id/element.h"
#include "../../id/equipmentID.h"
#include "../../id/equipType.h"
#include "../../id/itemQuality.h"
#include "../../id/statModType.h"

Eq_PowerOrb::Eq_PowerOrb() {
	name = "Power Orb";
	iconFilepath = "off_hand.png";
	itemQuality = ItemQuality::Common;
	weight = 1;
	tier = 1;

	textureFilepath = "power_orb.png";
	equipType = EquipType::OFF_HAND;
	equipmentID = EquipmentID::POWER_ORB;

	equipPower = 0;
	blockChance = 0.0;
	statMods = {};
}