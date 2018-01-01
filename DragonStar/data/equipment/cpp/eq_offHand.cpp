// ==================================
//
// eq_offHand.cpp
//
// ==================================

#include "../header/eq_offHand.h"

Eq_PowerOrb::Eq_PowerOrb() {
	name = "Iron Shield";
	iconFilepath = "off_hand.png";
	itemQuality = ItemQuality::COMMON;
	weight = 1;
	tier = 1;

	textureFilepath = "power_orb.png";
	equipType = EquipType::OFF_HAND;
	equipmentID = EquipmentID::POWER_ORB;

	equipPower = 0;
	blockChance = 0.0;
	statMods = {};
}