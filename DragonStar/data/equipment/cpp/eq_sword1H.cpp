// ==================================
//
// eq_sword1H.cpp
//
// ==================================

#include "../header/eq_sword1H.h"

#include "../../id/abilityID.h"
#include "../../id/auraID.h"
#include "../../id/category.h"
#include "../../id/element.h"
#include "../../id/equipmentID.h"
#include "../../id/equipType.h"
#include "../../id/itemQuality.h"
#include "../../id/statModType.h"

Eq_IronSword::Eq_IronSword() {
	name = "Iron Sword";
	iconFilepath = "sword.png";
	itemQuality = ItemQuality::Common;
	weight = 5;
	tier = 1;

	textureFilepath = "iron_sword.png";
	equipType = EquipType::SWORD_1H;
	equipmentID = EquipmentID::IRON_SWORD;

	equipPower = 50;
	attackSpeed = 200;
	attackRange = 1;
	attributeMultiplier = 1.00;
	attackElements = { Element::PHYSICAL };
	blockChance = 0.0;
	statMods = {};
}