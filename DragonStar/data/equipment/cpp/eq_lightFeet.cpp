// ==================================
//
// eq_lightFeet.cpp
//
// ==================================

#include "../header/eq_lightFeet.h"

#include "../../id/abilityID.h"
#include "../../id/auraID.h"
#include "../../id/category.h"
#include "../../id/element.h"
#include "../../id/equipmentID.h"
#include "../../id/equipType.h"
#include "../../id/itemQuality.h"
#include "../../id/statModType.h"

Eq_SilkShoes::Eq_SilkShoes() {
	name = "Silk Shoes";
	iconFilepath = "feet.png";
	itemQuality = ItemQuality::Common;
	weight = 2;
	tier = 1;

	textureFilepath = "silk_shoes.png";
	equipType = EquipType::LightFeet;
	equipmentID = EquipmentID::SilkShoes;

	equipPower = 2;
	blockChance = 0.0;
	statMods = {};
}