// ==================================
//
// eq_medBody.cpp
//
// ==================================

#include "../header/eq_medBody.h"

#include "../../id/abilityID.h"
#include "../../id/auraID.h"
#include "../../id/category.h"
#include "../../id/element.h"
#include "../../id/equipmentID.h"
#include "../../id/equipType.h"
#include "../../id/itemQuality.h"
#include "../../id/statModType.h"

Eq_LeatherArmor::Eq_LeatherArmor() {
	name = "Leather Armor";
	iconFilepath = "body.png";
	itemQuality = ItemQuality::Common;
	weight = 8;
	tier = 1;

	textureFilepath = "leather_armor.png";
	equipType = EquipType::MedBody;
	equipmentID = EquipmentID::LeatherArmor;

	equipPower = 16;
	blockChance = 0.0;
	statMods = {};
}