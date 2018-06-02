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

// --------------------------------------------------------------------

Eq_SilverRing::Eq_SilverRing() {
	name = "Silver Ring";
	iconFilepath = "ring.png";
	itemQuality = ItemQuality::Common;
	weight = 1;
	tier = 1;

	textureFilepath = "silver_ring.png";
	equipType = EquipType::Ring;
	equipmentID = EquipmentID::SilverRing;

	equipPower = 0;
	blockChance = 0.0;
	attackSpeed = 0.0;
	statMods = { };
}

// --------------------------------------------------------------------

Eq_GoldRing::Eq_GoldRing() {
	name = "Gold Ring";
	iconFilepath = "ring.png";
	itemQuality = ItemQuality::Common;
	weight = 1;
	tier = 3;

	textureFilepath = "gold_ring.png";
	equipType = EquipType::Ring;
	equipmentID = EquipmentID::GoldRing;

	equipPower = 0;
	blockChance = 0.0;
	attackSpeed = 0.0;
	statMods = {};
}

// --------------------------------------------------------------------

Eq_DragoniteRing::Eq_DragoniteRing() {
	name = "Dragonite Ring";
	iconFilepath = "ring.png";
	itemQuality = ItemQuality::Common;
	weight = 1;
	tier = 5;

	textureFilepath = "dragonite_ring.png";
	equipType = EquipType::Ring;
	equipmentID = EquipmentID::DragoniteRing;

	equipPower = 0;
	blockChance = 0.0;
	attackSpeed = 0.0;
	statMods = {};
}

// --------------------------------------------------------------------

Eq_BandOfTwinDisciplines::Eq_BandOfTwinDisciplines() {
	name = "Band of Twin Disciplines";
	iconFilepath = "ring.png";
	itemQuality = ItemQuality::Unique;
	weight = 1;
	tier = 1;

	textureFilepath = "band_of_twin_disciplines.png";
	equipType = EquipType::Ring;
	equipmentID = EquipmentID::BandOfTwinDisciplines;

	equipPower = 0;
	blockChance = 0.0;
	attackSpeed = 0.0;
	statMods = {
		StatMod(StatModType::MP, 5.0),
		StatMod(StatModType::INT, 3.0),
		StatMod(StatModType::Damage, 0.04, { Category::Any }, { Element::Light, Element::Dark }),
		StatMod(StatModType::Haste, 0.03),
		StatMod(StatModType::Resistance, 0.07, { Category::Any }, { Element::Light, Element::Dark })
	};
	extraAffixes = {
		"Casting a Light or Dark spell increases the damage of your next Mind spell by 10%. Stacks up to 5 times and lasts 15s."
	};
}

void Eq_BandOfTwinDisciplines::OnEvent(EventType eventType, ActorPtr& user, ActorPtr& target, BattleScene* battleScene, EventOptions& eventOptions, EventResult& eventResult, bool isOffHand, double& amount) {
	if (eventType == EventType::Hit) {
		auto cat = eventOptions.Categories;
		auto ele = eventOptions.Elements;

		if (std::find(cat.begin(), cat.end(), Category::Spell) != cat.end()) {
			if (std::find(ele.begin(), ele.end(), Element::Light) != ele.end() || std::find(ele.begin(), ele.end(), Element::Dark) != ele.end()) {
				Combat::AddAuraStack(user, user, AuraID::BandOfTwinDisciplines);
			}
		}
	}
}

// --------------------------------------------------------------------

Eq_RingOfVitality::Eq_RingOfVitality() {
	name = "Ring of Vitality";
	iconFilepath = "ring.png";
	itemQuality = ItemQuality::Unique;
	weight = 1;
	tier = 1;

	textureFilepath = "ring_of_vitality.png";
	equipType = EquipType::Ring;
	equipmentID = EquipmentID::RingOfVitality;

	equipPower = 0;
	blockChance = 0.0;
	attackSpeed = 0.0;
	statMods = {
		StatMod(StatModType::HP, 45.0),
		StatMod(StatModType::HPRegen, 5.0),
		StatMod(StatModType::VIT, 20.0),
		StatMod(StatModType::Resistance, 0.05, { Category::Any }, { Element::Physical })
	};
}

// --------------------------------------------------------------------

Eq_OmegaRing::Eq_OmegaRing() {
	name = "Omega Ring";
	iconFilepath = "ring.png";
	itemQuality = ItemQuality::Unique;
	weight = 1;
	tier = 6;

	textureFilepath = "omega_ring.png";
	equipType = EquipType::Ring;
	equipmentID = EquipmentID::OmegaRing;

	equipPower = 0;
	blockChance = 0.0;
	attackSpeed = 0.0;
	statMods = {
		StatMod(StatModType::HP, 50.0),
		StatMod(StatModType::MP, 10.0),
		StatMod(StatModType::SP, 5.0),
		StatMod(StatModType::AllAttributes, 3.0),
		StatMod(StatModType::Armor, 4.0),
		StatMod(StatModType::CritChance, 0.05),
		StatMod(StatModType::CritPower, 0.25),
		StatMod(StatModType::Haste, 0.04),
		StatMod(StatModType::DoubleStrikeChance, 0.08),
		StatMod(StatModType::Resistance, 0.15,{ Category::Any },{ Element::Fire, Element::Ice, Element::Lightning, Element::Poison, Element::Water, Element::Wind, Element::Earth, Element::Light, Element::Dark })
	};
}