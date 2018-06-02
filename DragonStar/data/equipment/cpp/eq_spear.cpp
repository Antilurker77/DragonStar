// ==================================
//
// eq_spear.cpp
//
// ==================================

#include "../header/eq_spear.h"

#include "../../id/abilityID.h"
#include "../../id/auraID.h"
#include "../../id/category.h"
#include "../../id/element.h"
#include "../../id/equipmentID.h"
#include "../../id/equipType.h"
#include "../../id/itemQuality.h"
#include "../../id/statModType.h"

Eq_IronSpear::Eq_IronSpear() {
	name = "Iron Spear";
	iconFilepath = "spear.png";
	itemQuality = ItemQuality::Common;
	weight = 10;
	tier = 1;

	textureFilepath = "iron_spear.png";
	equipType = EquipType::Spear;
	equipmentID = EquipmentID::IronSpear;

	equipPower = 80;
	attackSpeed = 250;
	attackRange = 1;
	attributeMultiplier = 1.6;
	attackElements = { Element::Physical };
	blockChance = 0.0;
	statMods = {};
}

// --------------------------------------------------------------------

Eq_CloudLance::Eq_CloudLance() {
	name = "Cloud Lance";
	iconFilepath = "spear.png";
	itemQuality = ItemQuality::Unique;
	weight = 10;
	tier = 1;

	textureFilepath = "iron_spear.png";
	equipType = EquipType::Spear;
	equipmentID = EquipmentID::CloudLance;

	equipPower = 80;
	attackSpeed = 250;
	attackRange = 1;
	attributeMultiplier = 1.6;
	attackElements = { Element::Physical };
	blockChance = 0.0;
	statMods = {
		StatMod(StatModType::DEX, 9.0),
		StatMod(StatModType::Damage, 0.1, { Category::Any }, { Element::Wind }),
		StatMod(StatModType::Haste, 0.08),
		StatMod(StatModType::ArmorPen, 0.15),
		StatMod(StatModType::OnHitDamage, 12.0, { Element::Wind }, { Category::Any }),
		StatMod(StatModType::MovementSpeed, 0.1),
		StatMod(StatModType::Resistance, 0.1, { Category::Any }, { Element::Wind })
	};
}