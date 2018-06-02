// ==================================
//
// eq_axe1H.cpp
//
// ==================================

#include "../header/eq_axe1H.h"

#include "../../id/abilityID.h"
#include "../../id/auraID.h"
#include "../../id/category.h"
#include "../../id/element.h"
#include "../../id/equipmentID.h"
#include "../../id/equipType.h"
#include "../../id/itemQuality.h"
#include "../../id/statModType.h"

Eq_IronAxe::Eq_IronAxe() {
	name = "Iron Axe";
	iconFilepath = "axe.png";
	itemQuality = ItemQuality::Common;
	weight = 6;
	tier = 1;

	textureFilepath = "iron_axe.png";
	equipType = EquipType::Axe1H;
	equipmentID = EquipmentID::IronAxe;

	equipPower = 55;
	attackSpeed = 220;
	attackRange = 1;
	attributeMultiplier = 1.10;
	attackElements = { Element::Physical };
	blockChance = 0.0;
	statMods = {};
}