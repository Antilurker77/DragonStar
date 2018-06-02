// ==================================
//
// eq_lightBody.cpp
//
// ==================================

#include "../header/eq_lightBody.h"

#include "../../id/abilityID.h"
#include "../../id/auraID.h"
#include "../../id/category.h"
#include "../../id/element.h"
#include "../../id/equipmentID.h"
#include "../../id/equipType.h"
#include "../../id/itemQuality.h"
#include "../../id/statModType.h"

Eq_SilkRobes::Eq_SilkRobes() {
	name = "Silk Robes";
	iconFilepath = "body.png";
	itemQuality = ItemQuality::Common;
	weight = 4;
	tier = 1;

	textureFilepath = "silk.png";
	equipType = EquipType::LightBody;
	equipmentID = EquipmentID::SilkRobes;

	equipPower = 8;
	blockChance = 0.0;
	statMods = {};
}