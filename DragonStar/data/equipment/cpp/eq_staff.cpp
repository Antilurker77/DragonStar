// ==================================
//
// eq_staff.cpp
//
// ==================================

#include "../header/eq_staff.h"

#include "../../id/abilityID.h"
#include "../../id/auraID.h"
#include "../../id/category.h"
#include "../../id/element.h"
#include "../../id/equipmentID.h"
#include "../../id/equipType.h"
#include "../../id/itemQuality.h"
#include "../../id/statModType.h"

Eq_WoodenStaff::Eq_WoodenStaff() {
	name = "Wooden Staff";
	iconFilepath = "staff.png";
	itemQuality = ItemQuality::Common;
	weight = 7;
	tier = 1;

	textureFilepath = "wooden_staff.png";
	equipType = EquipType::Staff;
	equipmentID = EquipmentID::WoodenStaff;

	equipPower = 40;
	attackSpeed = 260;
	attackRange = 1;
	attributeMultiplier = 0.8;
	attackElements = { Element::Physical };
	blockChance = 0.0;
	statMods = {};
}

// --------------------------------------------------------------------

Eq_StaffOfTheNovice::Eq_StaffOfTheNovice() {
	name = "Staff of the Novice";
	iconFilepath = "staff.png";
	itemQuality = ItemQuality::Unique;
	weight = 7;
	tier = 1;

	textureFilepath = "wooden_staff.png";
	equipType = EquipType::Staff;
	equipmentID = EquipmentID::StaffOfTheNovice;

	equipPower = 40;
	attackSpeed = 260;
	attackRange = 1;
	attributeMultiplier = 0.8;
	attackElements = { Element::Physical };
	blockChance = 0.0;
	statMods = {
		StatMod(StatModType::MP, 15),
		StatMod(StatModType::MPRegen, 2.5),
		StatMod(StatModType::INT, 8),
		StatMod(StatModType::Haste, 0.07),
		StatMod(StatModType::Damage, 0.10, AbilityID::MagicMissile),
		StatMod(StatModType::Damage, 0.10, AbilityID::FlameBolt),
		StatMod(StatModType::Damage, 0.10, AbilityID::Icicle),
		StatMod(StatModType::Damage, 0.10, AbilityID::Shock)
	};
}