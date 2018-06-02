// ==================================
//
// eq_medHead.cpp
//
// ==================================

#include "../header/eq_medHead.h"

#include "../../id/abilityID.h"
#include "../../id/auraID.h"
#include "../../id/category.h"
#include "../../id/element.h"
#include "../../id/equipmentID.h"
#include "../../id/equipType.h"
#include "../../id/itemQuality.h"
#include "../../id/statModType.h"

Eq_LeatherHelmet::Eq_LeatherHelmet() {
	name = "Leather Helmet";
	iconFilepath = "head.png";
	itemQuality = ItemQuality::Common;
	weight = 4;
	tier = 1;

	textureFilepath = "leather_helmet.png";
	equipType = EquipType::MED_HEAD;
	equipmentID = EquipmentID::LEATHER_HELMET;

	equipPower = 6;
	blockChance = 0.0;
	statMods = {};
}