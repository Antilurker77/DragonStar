// ==================================
//
// playerClassData.cpp
//
// ==================================

#include "playerClassData.h"

#include "../id/abilityType.h"
#include "../id/equipType.h"
#include "../id/playerClassID.h"

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
		EquipType::BUCKLER,
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
		{ AbilityType::TECH, 3u },
		{ AbilityType::SWORD_SKILL, 3u },
		{ AbilityType::AXE_SKILL, 3u },
		{ AbilityType::MACE_SKILL, 3u },
		{ AbilityType::DAGGER_SKILL, 3u },
		{ AbilityType::CLAW_SKILL, 3u },
		{ AbilityType::SPEAR_SKILL, 3u },
		{ AbilityType::BOW_SKILL, 3u },
		{ AbilityType::SHIELD_SKILL, 3u },
		{ AbilityType::ARCANE_SPELL, 3u },
		{ AbilityType::FIRE_SPELL, 3u },
		{ AbilityType::ICE_SPELL, 3u },
		{ AbilityType::LIGHTNING_SPELL, 3u },
		{ AbilityType::POISON_SPELL, 3u },
		{ AbilityType::WATER_SPELL, 3u },
		{ AbilityType::WIND_SPELL, 3u },
		{ AbilityType::EARTH_SPELL, 3u },
		{ AbilityType::MIND_SPELL, 3u },
		{ AbilityType::LIGHT_SPELL, 3u },
		{ AbilityType::DARK_SPELL, 3u },
		{ AbilityType::SPIRIT_SPELL, 3u },
		{ AbilityType::ASTRAL_SPELL, 3u },
		{ AbilityType::DIVINE_HEAL, 3u },
		{ AbilityType::NATURE_HEAL, 3u },
		{ AbilityType::ASTRAL_HEAL, 3u },
	};
}

Pc_Blademaster::Pc_Blademaster() {
	name = "Blademaster";
	playerClassID = PlayerClassID::BLADEMASTER;

	equippable = {
		EquipType::SWORD_1H,
		EquipType::SWORD_2H,
		EquipType::SHIELD,
		EquipType::BUCKLER,
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
		{ AbilityType::TECH, 3u },
		{ AbilityType::SWORD_SKILL, 3u },
		{ AbilityType::SHIELD_SKILL, 2u },
		{ AbilityType::ARCANE_SPELL, 1u },
		{ AbilityType::FIRE_SPELL, 1u },
		{ AbilityType::WATER_SPELL, 1u },
		{ AbilityType::WIND_SPELL, 1u },
		{ AbilityType::EARTH_SPELL, 1u },
	};
}

Pc_Berserker::Pc_Berserker() {
	name = "Berserker";
	playerClassID = PlayerClassID::BERSERKER;

	equippable = {
		EquipType::AXE_1H,
		EquipType::AXE_2H,
		EquipType::SHIELD,
		EquipType::BUCKLER,
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
		{ AbilityType::TECH, 3u },
		{ AbilityType::AXE_SKILL, 3u },
		{ AbilityType::SHIELD_SKILL, 2u }
	};
}

Pc_Guardian::Pc_Guardian() {
	name = "Guardian";
	playerClassID = PlayerClassID::GUARDIAN;

	equippable = {
		EquipType::MACE_1H,
		EquipType::MACE_2H,
		EquipType::SHIELD,
		EquipType::BUCKLER,
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
		{ AbilityType::TECH, 3u },
		{ AbilityType::MACE_SKILL, 3u },
		{ AbilityType::SHIELD_SKILL, 3u },
		{ AbilityType::ICE_SPELL, 1u },
		{ AbilityType::LIGHTNING_SPELL, 1u },
		{ AbilityType::EARTH_SPELL, 1u },
		{ AbilityType::LIGHT_SPELL, 1u },
		{ AbilityType::DIVINE_HEAL, 2u }
	};
}

Pc_Assassin::Pc_Assassin() {
	name = "Assassin";
	playerClassID = PlayerClassID::ASSASSIN;

	equippable = {
		EquipType::DAGGER,
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
		{ AbilityType::TECH, 3u },
		{ AbilityType::DAGGER_SKILL, 3u },
		{ AbilityType::POISON_SPELL, 1u },
		{ AbilityType::DARK_SPELL, 1u },
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
		{ AbilityType::TECH, 3u },
		{ AbilityType::SPEAR_SKILL, 3u },
		{ AbilityType::LIGHTNING_SPELL, 1u },
		{ AbilityType::WATER_SPELL, 1u },
		{ AbilityType::WIND_SPELL, 1u },
	};
}

Pc_Ranger::Pc_Ranger() {
	name = "Ranger";
	playerClassID = PlayerClassID::RANGER;

	equippable = {
		EquipType::BOW,
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
		{ AbilityType::TECH, 3u },
		{ AbilityType::BOW_SKILL, 3u },
		{ AbilityType::ARCANE_SPELL, 1u },
		{ AbilityType::FIRE_SPELL, 1u },
		{ AbilityType::ICE_SPELL, 1u },
		{ AbilityType::LIGHTNING_SPELL, 1u },
		{ AbilityType::POISON_SPELL, 1u },
		{ AbilityType::WATER_SPELL, 1u },
		{ AbilityType::WIND_SPELL, 1u },
		{ AbilityType::EARTH_SPELL, 1u },
		{ AbilityType::LIGHT_SPELL, 1u },
		{ AbilityType::DARK_SPELL, 1u },
	};
}

Pc_Wizard::Pc_Wizard() {
	name = "Wizard";
	playerClassID = PlayerClassID::WIZARD;

	equippable = {
		EquipType::WAND,
		EquipType::STAFF,
		EquipType::SHIELD,
		EquipType::BUCKLER,
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
		{ AbilityType::ARCANE_SPELL, 3u },
		{ AbilityType::FIRE_SPELL, 3u },
		{ AbilityType::ICE_SPELL, 3u },
		{ AbilityType::LIGHTNING_SPELL, 3u },
		{ AbilityType::ASTRAL_SPELL, 3u }
	};
}

Pc_Shaman::Pc_Shaman() {
	name = "Shaman";
	playerClassID = PlayerClassID::SHAMAN;

	equippable = {
		EquipType::WAND,
		EquipType::STAFF,
		EquipType::SHIELD,
		EquipType::BUCKLER,
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
		{ AbilityType::POISON_SPELL, 3u },
		{ AbilityType::WATER_SPELL, 3u },
		{ AbilityType::WIND_SPELL, 3u },
		{ AbilityType::EARTH_SPELL, 3u },
		{ AbilityType::ASTRAL_SPELL, 3u },
		{ AbilityType::NATURE_HEAL, 1u }
	};
}

Pc_Acolyte::Pc_Acolyte() {
	name = "Acolyte";
	playerClassID = PlayerClassID::ACOLYTE;

	equippable = {
		EquipType::WAND,
		EquipType::STAFF,
		EquipType::SHIELD,
		EquipType::BUCKLER,
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
		{ AbilityType::MIND_SPELL, 3u },
		{ AbilityType::LIGHT_SPELL, 3u },
		{ AbilityType::DARK_SPELL, 3u },
		{ AbilityType::ASTRAL_SPELL, 3u },
		{ AbilityType::DIVINE_HEAL, 1u },
	};
}

Pc_Priest::Pc_Priest() {
	name = "Priest";
	playerClassID = PlayerClassID::PRIEST;

	equippable = {
		EquipType::WAND,
		EquipType::STAFF,
		EquipType::SHIELD,
		EquipType::BUCKLER,
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
		{ AbilityType::LIGHT_SPELL, 1u },
		{ AbilityType::DIVINE_HEAL, 3u },
		{ AbilityType::ASTRAL_HEAL, 3u },
	};
}

Pc_Druid::Pc_Druid() {
	name = "Druid";
	playerClassID = PlayerClassID::DRUID;

	equippable = {
		EquipType::WAND,
		EquipType::STAFF,
		EquipType::SHIELD,
		EquipType::BUCKLER,
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
		{ AbilityType::WATER_SPELL, 1u },
		{ AbilityType::WIND_SPELL, 1u },
		{ AbilityType::EARTH_SPELL, 1u },
		{ AbilityType::NATURE_HEAL, 3u },
		{ AbilityType::ASTRAL_HEAL, 3u },
	};
}