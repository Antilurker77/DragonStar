// ==================================
//
// eq_bow.cpp
//
// ==================================

#include "../header/eq_bow.h"

#include "../../id/abilityID.h"
#include "../../id/auraID.h"
#include "../../id/category.h"
#include "../../id/element.h"
#include "../../id/equipmentID.h"
#include "../../id/equipType.h"
#include "../../id/itemQuality.h"
#include "../../id/statModType.h"

Eq_Longbow::Eq_Longbow() {
	name = "Longbow";
	iconFilepath = "longbow.png";
	itemQuality = ItemQuality::COMMON;
	weight = 4;
	tier = 1;

	textureFilepath = "longbow.png";
	equipType = EquipType::BOW;
	equipmentID = EquipmentID::LONGBOW;

	equipPower = 55;
	attackSpeed = 240;
	attackRange = 4;
	attributeMultiplier = 1.1;
	attackElements = { Element::PHYSICAL };
	blockChance = 0.0;
	statMods = {};
}