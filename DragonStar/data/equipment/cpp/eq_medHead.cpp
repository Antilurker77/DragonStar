// ==================================
//
// eq_medHead.cpp
//
// ==================================

#include "../header/eq_medHead.h"

Eq_LeatherHelmet::Eq_LeatherHelmet() {
	name = "Leather Helmet";
	iconFilepath = "head.png";
	itemQuality = ItemQuality::COMMON;
	weight = 4;
	tier = 1;

	textureFilepath = "leather_helmet.png";
	equipType = EquipType::MED_HEAD;
	equipmentID = EquipmentID::LEATHER_HELMET;

	equipPower = 6;
	blockChance = 0.0;
	statMods = {};
}