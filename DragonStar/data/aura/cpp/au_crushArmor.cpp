// ==================================
//
// au_crushArmor.cpp
//
// ==================================

#include "../header/au_crushArmor.h"

#include "../../id/abilityID.h"
#include "../../id/attribute.h"
#include "../../id/auraID.h"
#include "../../id/category.h"
#include "../../id/element.h"
#include "../../id/statModType.h"

Au_CrushArmor::Au_CrushArmor() {
	name = "Crush Armor";
	id = AuraID::CrushArmor;
	icon = "crush_armor.png";

	categories = {
		Category::Attack
	};

	elements = {
		Element::Physical
	};

	statMods = {
		StatMod(StatModType::ArmorMult, -0.2)
	};

	canCrit = false;

	baseDuration = 1200;
	timePerTick = 0;
	maxStacks = 1;
	hasTicks = false;
	fixedDuration = false; // if true, ignore VIT in calculations
	unlimitedDuration = false;
	consumedOnUse = false; // if true, aura will expire when called in combat calculations
	isBuff = false;

	isStun = false;
	isDisarm = false;
	isSilence = false;
	isSlow = false;

	uniquePerActor = true; // determines if one actor can apply multiple copies of aura
	uniqueAura = true; // if true only one copy can be applied regardless of source

	removeAllStacksOnExpiration = false; // Determines whether all stacks or 1 stack are removed when aura expires
}

std::string Au_CrushArmor::GetDescription() {
	return "Reduces armor by 20%.";
}