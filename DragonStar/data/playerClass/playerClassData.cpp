// ==================================
//
// playerClassData.cpp
//
// ==================================

#include "playerClassData.h"

Pc_Adventurer::Pc_Adventurer() {
	name = "Adventurer";
	playerClassID = PlayerClassID::ADVENTURER;

	equippable = {
		EquipType::SWORD_1H,
		EquipType::SWORD_2H,
		EquipType::AXE_1H,
		EquipType::AXE_2H,
		EquipType::MACE_1H,
		EquipType::MACE_2H,
		EquipType::DAGGER,
		EquipType::CLAW,
		EquipType::SPEAR,
		EquipType::BOW,
		EquipType::WAND,
		EquipType::STAFF,
		EquipType::SHIELD,
		EquipType::OFF_HAND,
		EquipType::HEAVY_BODY,
		EquipType::HEAVY_FEET,
		EquipType::HEAVY_HANDS,
		EquipType::HEAVY_HEAD,
		EquipType::LIGHT_BODY,
		EquipType::LIGHT_FEET,
		EquipType::LIGHT_HANDS,
		EquipType::LIGHT_HEAD,
		EquipType::MED_BODY,
		EquipType::MED_FEET,
		EquipType::MED_HANDS,
		EquipType::MED_HEAD,
		EquipType::RING,
		EquipType::NECK,
		EquipType::TRINKET
	};

	usable = {
		{ AbilityType::TECH, 4u },
		{ AbilityType::SWORD_SKILL, 4u },
		{ AbilityType::AXE_SKILL, 4u },
		{ AbilityType::MACE_SKILL, 4u },
		{ AbilityType::DAGGER_SKILL, 4u },
		{ AbilityType::CLAW_SKILL, 4u },
		{ AbilityType::SPEAR_SKILL, 4u },
		{ AbilityType::BOW_SKILL, 4u },
		{ AbilityType::SHIELD_SKILL, 4u },
		{ AbilityType::ARCANE_SPELL, 4u },
		{ AbilityType::FIRE_SPELL, 4u },
		{ AbilityType::ICE_SPELL, 4u },
		{ AbilityType::LIGHTNING_SPELL, 4u },
		{ AbilityType::POISON_SPELL, 4u },
		{ AbilityType::WATER_SPELL, 4u },
		{ AbilityType::WIND_SPELL, 4u },
		{ AbilityType::EARTH_SPELL, 4u },
		{ AbilityType::MIND_SPELL, 4u },
		{ AbilityType::LIGHT_SPELL, 4u },
		{ AbilityType::DARK_SPELL, 4u },
		{ AbilityType::SPIRIT_SPELL, 4u },
		{ AbilityType::ASTRAL_SPELL, 4u },
		{ AbilityType::DIVINE_HEAL, 4u },
		{ AbilityType::NATURE_HEAL, 4u },
		{ AbilityType::ASTRAL_HEAL, 4u },
	};
}

Pc_Blademaster::Pc_Blademaster() {
	name = "Blademaster";
	playerClassID = PlayerClassID::BLADEMASTER;

	equippable = {
		EquipType::SWORD_1H,
		EquipType::SWORD_2H,
		EquipType::SHIELD,
		EquipType::HEAVY_BODY,
		EquipType::HEAVY_FEET,
		EquipType::HEAVY_HANDS,
		EquipType::HEAVY_HEAD,
		EquipType::LIGHT_BODY,
		EquipType::LIGHT_FEET,
		EquipType::LIGHT_HANDS,
		EquipType::LIGHT_HEAD,
		EquipType::MED_BODY,
		EquipType::MED_FEET,
		EquipType::MED_HANDS,
		EquipType::MED_HEAD,
		EquipType::RING,
		EquipType::NECK,
		EquipType::TRINKET
	};

	usable = {
		{ AbilityType::TECH, 4u },
		{ AbilityType::SWORD_SKILL, 4u },
		{ AbilityType::ARCANE_SPELL, 2u },
		{ AbilityType::FIRE_SPELL, 2u },
		{ AbilityType::WATER_SPELL, 2u },
		{ AbilityType::WIND_SPELL, 2u },
		{ AbilityType::EARTH_SPELL, 2u },
	};
}

Pc_Stormsinger::Pc_Stormsinger() {
	name = "Stormsinger";
	playerClassID = PlayerClassID::STORMSINGER;

	equippable = {
		EquipType::SPEAR,
		EquipType::HEAVY_BODY,
		EquipType::HEAVY_FEET,
		EquipType::HEAVY_HANDS,
		EquipType::HEAVY_HEAD,
		EquipType::LIGHT_BODY,
		EquipType::LIGHT_FEET,
		EquipType::LIGHT_HANDS,
		EquipType::LIGHT_HEAD,
		EquipType::MED_BODY,
		EquipType::MED_FEET,
		EquipType::MED_HANDS,
		EquipType::MED_HEAD,
		EquipType::RING,
		EquipType::NECK,
		EquipType::TRINKET
	};

	usable = {
		{ AbilityType::TECH, 4u },
		{ AbilityType::SPEAR_SKILL, 4u },
		{ AbilityType::LIGHTNING_SPELL, 1u },
		{ AbilityType::WATER_SPELL, 1u },
		{ AbilityType::WIND_SPELL, 1u },
	};
}