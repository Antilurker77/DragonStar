// ==================================
//
// eq_lightHead.cpp
//
// ==================================

#include "../header/eq_lightHead.h"

#include "../../id/abilityID.h"
#include "../../id/auraID.h"
#include "../../id/category.h"
#include "../../id/element.h"
#include "../../id/equipmentID.h"
#include "../../id/equipType.h"
#include "../../id/itemQuality.h"
#include "../../id/statModType.h"

Eq_SilkHat::Eq_SilkHat() {
	name = "Silk Hat";
	iconFilepath = "head.png";
	itemQuality = ItemQuality::COMMON;
	weight = 2;
	tier = 1;

	textureFilepath = "silk_hat.png";
	equipType = EquipType::LIGHT_HEAD;
	equipmentID = EquipmentID::SILK_HAT;

	equipPower = 3;
	blockChance = 0.0;
	statMods = {};
}