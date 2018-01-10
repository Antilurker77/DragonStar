// ==================================
//
// eq_staff.cpp
//
// ==================================

#include "../header/eq_staff.h"

#include "../../id/abilityID.h"
#include "../../id/auraID.h"
#include "../../id/category.h"
#include "../../id/element.h"
#include "../../id/equipmentID.h"
#include "../../id/equipType.h"
#include "../../id/itemQuality.h"
#include "../../id/statModType.h"

Eq_WoodenStaff::Eq_WoodenStaff() {
	name = "Wooden Staff";
	iconFilepath = "staff.png";
	itemQuality = ItemQuality::COMMON;
	weight = 7;
	tier = 1;

	textureFilepath = "wooden_staff.png";
	equipType = EquipType::STAFF;
	equipmentID = EquipmentID::WOODEN_STAFF;

	equipPower = 40;
	attackSpeed = 260;
	attackRange = 1;
	attributeMultiplier = 0.8;
	attackElements = { Element::PHYSICAL };
	blockChance = 0.0;
	statMods = {};
}