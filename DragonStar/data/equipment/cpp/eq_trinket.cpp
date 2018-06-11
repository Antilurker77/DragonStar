// ==================================
//
// eq_trinket.cpp
//
// ==================================

#include "../header/eq_trinket.h"

#include "../../id/abilityID.h"
#include "../../id/auraID.h"
#include "../../id/category.h"
#include "../../id/element.h"
#include "../../id/equipmentID.h"
#include "../../id/equipType.h"
#include "../../id/itemQuality.h"
#include "../../id/statModType.h"

// --------------------------------------------------------------------

Eq_CharmOfStrength::Eq_CharmOfStrength() {
	name = "Charm of Strength";
	iconFilepath = "trinket.png";
	itemQuality = ItemQuality::Unique;
	weight = 1;
	tier = 1;

	textureFilepath = "trinket.png";
	equipType = EquipType::Trinket;
	equipmentID = EquipmentID::CharmOfStrength;

	equipPower = 0;
	blockChance = 0.0;
	attackSpeed = 0.0;
	statMods = {
		StatMod(StatModType::STRMult, 0.1)
	};
}

// --------------------------------------------------------------------

Eq_CharmOfDexterity::Eq_CharmOfDexterity() {
	name = "Charm of Dexterity";
	iconFilepath = "trinket.png";
	itemQuality = ItemQuality::Unique;
	weight = 1;
	tier = 1;

	textureFilepath = "trinket.png";
	equipType = EquipType::Trinket;
	equipmentID = EquipmentID::CharmOfDexterity;

	equipPower = 0;
	blockChance = 0.0;
	attackSpeed = 0.0;
	statMods = {
		StatMod(StatModType::DEXMult, 0.1)
	};
}

// --------------------------------------------------------------------

Eq_CharmOfIntelligence::Eq_CharmOfIntelligence() {
	name = "Charm of Intelligence";
	iconFilepath = "trinket.png";
	itemQuality = ItemQuality::Unique;
	weight = 1;
	tier = 1;

	textureFilepath = "trinket.png";
	equipType = EquipType::Trinket;
	equipmentID = EquipmentID::CharmOfIntelligence;

	equipPower = 0;
	blockChance = 0.0;
	attackSpeed = 0.0;
	statMods = {
		StatMod(StatModType::INTMult, 0.1)
	};
}

// --------------------------------------------------------------------

Eq_CharmOfWisdom::Eq_CharmOfWisdom() {
	name = "Charm of Wisdom";
	iconFilepath = "trinket.png";
	itemQuality = ItemQuality::Unique;
	weight = 1;
	tier = 1;

	textureFilepath = "trinket.png";
	equipType = EquipType::Trinket;
	equipmentID = EquipmentID::CharmOfWisdom;

	equipPower = 0;
	blockChance = 0.0;
	attackSpeed = 0.0;
	statMods = {
		StatMod(StatModType::WISMult, 0.1)
	};
}

// --------------------------------------------------------------------

Eq_CharmOfConstitution::Eq_CharmOfConstitution() {
	name = "Charm of Constitution";
	iconFilepath = "trinket.png";
	itemQuality = ItemQuality::Unique;
	weight = 1;
	tier = 1;

	textureFilepath = "trinket.png";
	equipType = EquipType::Trinket;
	equipmentID = EquipmentID::CharmOfConstitution;

	equipPower = 0;
	blockChance = 0.0;
	attackSpeed = 0.0;
	statMods = {
		StatMod(StatModType::HPMult, 0.15)
	};
}

// --------------------------------------------------------------------

Eq_SpringWaterStone::Eq_SpringWaterStone() {
	name = "Spring Water Stone";
	iconFilepath = "trinket.png";
	itemQuality = ItemQuality::Unique;
	weight = 1;
	tier = 1;

	textureFilepath = "trinket.png";
	equipType = EquipType::Trinket;
	equipmentID = EquipmentID::SpringWaterStone;

	equipPower = 0;
	blockChance = 0.0;
	attackSpeed = 0.0;
	statMods = {
		StatMod(StatModType::MPMult, 0.1),
		StatMod(StatModType::MPRegen, 2.0)
	};
}

// --------------------------------------------------------------------