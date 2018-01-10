// ==================================
//
// eq_heavyHead.cpp
//
// ==================================

#include "../header/eq_heavyHead.h"

#include "../../id/abilityID.h"
#include "../../id/auraID.h"
#include "../../id/category.h"
#include "../../id/element.h"
#include "../../id/equipmentID.h"
#include "../../id/equipType.h"
#include "../../id/itemQuality.h"
#include "../../id/statModType.h"

Eq_IronHelm::Eq_IronHelm() {
	name = "Iron Helm";
	iconFilepath = "head.png";
	itemQuality = ItemQuality::COMMON;
	weight = 8;
	tier = 1;

	textureFilepath = "iron_helm.png";
	equipType = EquipType::HEAVY_HEAD;
	equipmentID = EquipmentID::IRON_HELM;

	equipPower = 9;
	blockChance = 0.0;
	statMods = {};
}