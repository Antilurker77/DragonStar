// ==================================
//
// eq_sword2H.cpp
//
// ==================================

#include "../header/eq_sword2H.h"

#include "../../id/abilityID.h"
#include "../../id/auraID.h"
#include "../../id/category.h"
#include "../../id/element.h"
#include "../../id/equipmentID.h"
#include "../../id/equipType.h"
#include "../../id/itemQuality.h"
#include "../../id/statModType.h"

Eq_IronGreatsword::Eq_IronGreatsword() {
	name = "Iron Greatsword";
	iconFilepath = "sword.png";
	itemQuality = ItemQuality::Common;
	weight = 9;
	tier = 1;

	textureFilepath = "iron_greatsword.png";
	equipType = EquipType::Sword2H;
	equipmentID = EquipmentID::IronGreatsword;

	equipPower = 100;
	attackSpeed = 300;
	attackRange = 1;
	attributeMultiplier = 2.00;
	attackElements = { Element::Physical };
	blockChance = 0.0;
	statMods = {};
}

// --------------------------------------------------------------------

Eq_HowlingSands::Eq_HowlingSands() {
	name = "Howling Sands";
	iconFilepath = "sword.png";
	itemQuality = ItemQuality::Unique;
	weight = 9;
	tier = 1;

	textureFilepath = "iron_greatsword.png";
	equipType = EquipType::Sword2H;
	equipmentID = EquipmentID::HowlingSands;

	equipPower = 100;
	attackSpeed = 300;
	attackRange = 1;
	attributeMultiplier = 2.00;
	attackElements = { Element::Wind, Element::Earth };
	blockChance = 0.0;
	statMods = {
		StatMod(StatModType::SPRegen, 1.2),
		StatMod(StatModType::STR, 9),
		StatMod(StatModType::OnHitDamage, 10.0, { Element::Wind }, { Category::Any }),
		StatMod(StatModType::OnHitDamage, 10.0, { Element::Earth }, { Category::Any }),
		StatMod(StatModType::CritChance, 0.14),
		StatMod(StatModType::Haste, 0.08)
	};
}