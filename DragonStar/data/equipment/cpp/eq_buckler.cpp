// ==================================
//
// eq_buckler.cpp
//
// ==================================

#include "../header/eq_buckler.h"

Eq_IronBuckler::Eq_IronBuckler() {
	name = "Iron Buckler";
	iconFilepath = "shield.png";
	itemQuality = ItemQuality::COMMON;
	weight = 4;
	tier = 1;

	textureFilepath = "iron_buckler.png";
	equipType = EquipType::BUCKLER;
	equipmentID = EquipmentID::IRON_BUCKLER;

	equipPower = 7;
	blockChance = 0.04;
	statMods = {};
}