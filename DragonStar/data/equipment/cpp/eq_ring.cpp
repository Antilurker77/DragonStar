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

Eq_RingOfVitality::Eq_RingOfVitality() {
	name = "Ring of Vitality";
	iconFilepath = "ring.png";
	itemQuality = ItemQuality::UNIQUE;
	weight = 1;
	tier = 1;

	textureFilepath = "ring_of_vitality.png";
	equipType = EquipType::RING;
	equipmentID = EquipmentID::RING_OF_VITALITY;

	equipPower = 0;
	blockChance = 0.0;
	attackSpeed = 0.0;
	statMods = {
		StatMod(StatModType::HP, 45.0),
		StatMod(StatModType::HP_REGEN, 5.0),
		StatMod(StatModType::VIT, 20.0),
		StatMod(StatModType::RESISTANCE, 0.05, { Category::ANY }, { Element::PHYSICAL })
	};
}

Eq_OmegaRing::Eq_OmegaRing() {
	name = "Omega Ring";
	iconFilepath = "ring.png";
	itemQuality = ItemQuality::UNIQUE;
	weight = 1;
	tier = 4;

	textureFilepath = "omega_ring.png";
	equipType = EquipType::RING;
	equipmentID = EquipmentID::OMEGA_RING;

	equipPower = 0;
	blockChance = 0.0;
	attackSpeed = 0.0;
	statMods = {
		StatMod(StatModType::HP, 100.0),
		StatMod(StatModType::MP, 20.0),
		StatMod(StatModType::SP, 5.0),
		StatMod(StatModType::ALL_ATTRIBUTES, 5.0),
		StatMod(StatModType::ARMOR, 10.0),
		StatMod(StatModType::CRIT_CHANCE, 0.05),
		StatMod(StatModType::CRIT_DAMAGE, 0.25),
		StatMod(StatModType::HASTE, 0.04),
		StatMod(StatModType::DOUBLE_STRIKE_CHANCE, 0.08),
		StatMod(StatModType::RESISTANCE, 0.15,{ Category::ANY },{ Element::FIRE, Element::ICE, Element::LIGHTNING, Element::POISON, Element::WATER, Element::WIND, Element::EARTH, Element::LIGHT, Element::DARK })
	};
}