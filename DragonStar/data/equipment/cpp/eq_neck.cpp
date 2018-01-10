// ==================================
//
// eq_neck.cpp
//
// ==================================

#include "../header/eq_neck.h"

#include "../../id/abilityID.h"
#include "../../id/auraID.h"
#include "../../id/category.h"
#include "../../id/element.h"
#include "../../id/equipmentID.h"
#include "../../id/equipType.h"
#include "../../id/itemQuality.h"
#include "../../id/statModType.h"

Eq_SilverNecklace::Eq_SilverNecklace() {
	name = "Silver Necklace";
	iconFilepath = "neck.png";
	itemQuality = ItemQuality::COMMON;
	weight = 1;
	tier = 1;

	textureFilepath = "silver_necklace.png";
	equipType = EquipType::NECK;
	equipmentID = EquipmentID::SILVER_NECKLACE;

	equipPower = 0;
	blockChance = 0.0;
	attackSpeed = 0.0;
	statMods = {};
}

Eq_GoldNecklace::Eq_GoldNecklace() {
	name = "Gold Necklace";
	iconFilepath = "neck.png";
	itemQuality = ItemQuality::COMMON;
	weight = 1;
	tier = 3;

	textureFilepath = "gold_necklace.png";
	equipType = EquipType::NECK;
	equipmentID = EquipmentID::GOLD_NECKLACE;

	equipPower = 0;
	blockChance = 0.0;
	attackSpeed = 0.0;
	statMods = {};
}

Eq_DragoniteNecklace::Eq_DragoniteNecklace() {
	name = "Dragonite Necklace";
	iconFilepath = "neck.png";
	itemQuality = ItemQuality::COMMON;
	weight = 1;
	tier = 5;

	textureFilepath = "dragonite_necklace.png";
	equipType = EquipType::NECK;
	equipmentID = EquipmentID::DRAGONITE_NECKLACE;

	equipPower = 0;
	blockChance = 0.0;
	attackSpeed = 0.0;
	statMods = {};
}