// ==================================
//
// eq_ring.cpp
//
// ==================================

#include "../header/eq_ring.h"

#include "../../id/abilityID.h"
#include "../../id/auraID.h"
#include "../../id/category.h"
#include "../../id/element.h"
#include "../../id/equipmentID.h"
#include "../../id/equipType.h"
#include "../../id/itemQuality.h"
#include "../../id/statModType.h"

Eq_SilverRing::Eq_SilverRing() {
	name = "Silver Ring";
	iconFilepath = "ring.png";
	itemQuality = ItemQuality::COMMON;
	weight = 1;
	tier = 1;

	textureFilepath = "silver_ring.png";
	equipType = EquipType::RING;
	equipmentID = EquipmentID::SILVER_RING;

	equipPower = 0;
	blockChance = 0.0;
	attackSpeed = 0.0;
	statMods = { };
}

Eq_GoldRing::Eq_GoldRing() {
	name = "Gold Ring";
	iconFilepath = "ring.png";
	itemQuality = ItemQuality::COMMON;
	weight = 1;
	tier = 3;

	textureFilepath = "gold_ring.png";
	equipType = EquipType::RING;
	equipmentID = EquipmentID::GOLD_RING;

	equipPower = 0;
	blockChance = 0.0;
	attackSpeed = 0.0;
	statMods = {};
}

Eq_DragoniteRing::Eq_DragoniteRing() {
	name = "Dragonite Ring";
	iconFilepath = "ring.png";
	itemQuality = ItemQuality::COMMON;
	weight = 1;
	tier = 5;

	textureFilepath = "dragonite_ring.png";
	equipType = EquipType::RING;
	equipmentID = EquipmentID::DRAGONITE_RING;

	equipPower = 0;
	blockChance = 0.0;
	attackSpeed = 0.0;
	statMods = {};
}