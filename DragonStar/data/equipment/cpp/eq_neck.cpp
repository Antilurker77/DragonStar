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
	itemQuality = ItemQuality::Common;
	weight = 1;
	tier = 1;

	textureFilepath = "silver_necklace.png";
	equipType = EquipType::Neck;
	equipmentID = EquipmentID::SilverNecklace;

	equipPower = 0;
	blockChance = 0.0;
	attackSpeed = 0.0;
	statMods = {};
}

Eq_GoldNecklace::Eq_GoldNecklace() {
	name = "Gold Necklace";
	iconFilepath = "neck.png";
	itemQuality = ItemQuality::Common;
	weight = 1;
	tier = 3;

	textureFilepath = "gold_necklace.png";
	equipType = EquipType::Neck;
	equipmentID = EquipmentID::GoldNecklace;

	equipPower = 0;
	blockChance = 0.0;
	attackSpeed = 0.0;
	statMods = {};
}

Eq_DragoniteNecklace::Eq_DragoniteNecklace() {
	name = "Dragonite Necklace";
	iconFilepath = "neck.png";
	itemQuality = ItemQuality::Common;
	weight = 1;
	tier = 5;

	textureFilepath = "dragonite_necklace.png";
	equipType = EquipType::Neck;
	equipmentID = EquipmentID::DragoniteNecklace;

	equipPower = 0;
	blockChance = 0.0;
	attackSpeed = 0.0;
	statMods = {};
}

Eq_AmuletOfDivineLight::Eq_AmuletOfDivineLight() {
	name = "Amulet of Divine Light";
	iconFilepath = "neck.png";
	itemQuality = ItemQuality::Unique;
	weight = 1;
	tier = 1;

	textureFilepath = "amulet_of_divine_light.png";
	equipType = EquipType::Neck;
	equipmentID = EquipmentID::AmuletOfDivineLight;

	equipPower = 0;
	blockChance = 0.0;
	attackSpeed = 0.0;
	statMods = {
		StatMod(StatModType::MP, 10.0),
		StatMod(StatModType::MPRegen, 1.0),
		StatMod(StatModType::WIS, 3.0),
		StatMod(StatModType::Healing, 0.05, { Category::Any }, { Element::DivineHeal }),
		StatMod(StatModType::Haste, 0.03),
		StatMod(StatModType::MPCostReduction, 0.03),
		StatMod(StatModType::Resistance, 0.25, { Category::Any }, { Element::Dark })
	};
}