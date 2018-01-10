// ==================================
//
// au_gale.cpp
//
// ==================================

#include "../header/au_gale.h"

#include "../../id/abilityID.h"
#include "../../id/attribute.h"
#include "../../id/auraID.h"
#include "../../id/category.h"
#include "../../id/element.h"
#include "../../id/statModType.h"

Au_Gale::Au_Gale() {
	name = "Gale";
	id = AuraID::GALE;
	icon = "gale.png";

	categories = {
		Category::SPELL
	};

	elements = {
		Element::WIND
	};

	statMods = {
		StatMod(StatModType::CAST_TIME_REDUCTION, 10.0, AbilityID::GALE)
	};

	canCrit = false;

	baseDuration = 500;
	timePerTick = 100;
	maxStacks = 5;
	multiplyStatModsByStack = true; // if true, multiply stat mod by number of stacks.
	hasTicks = false;
	fixedDuration = false; // if true, ignore VIT in calculations
	unlimitedDuration = false;
	consumedOnUse = false; // if true, aura will expire when called in combat calculations
	isBuff = true;

	isStun = false;
	isDisarm = false;
	isSilence = false;
	isSlow = false;

	uniquePerActor = true; // determines if one actor can apply multiple copies of aura
	uniqueAura = true; // if true only one copy can be applied regardless of source

	removeAllStacksOnExpiration = false; // Determines whether all stacks or 1 stack are removed when aura expires
}

std::string Au_Gale::GetDescription() {
	return "Reduces the cast time of Gale by 0." + std::to_string(stackCount) + "s.";
}