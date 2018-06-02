// ==================================
//
// au_icicle.cpp
//
// ==================================

#include "../header/au_icicle.h"

#include "../../id/abilityID.h"
#include "../../id/attribute.h"
#include "../../id/auraID.h"
#include "../../id/category.h"
#include "../../id/element.h"
#include "../../id/statModType.h"

Au_Icicle::Au_Icicle() {
	name = "Icicle";
	id = AuraID::Icicle;
	icon = "icicle.png";

	categories = {
		Category::Spell
	};

	elements = {
		Element::Ice
	};

	statMods = {
		StatMod(StatModType::MovementSpeed, -0.2)
	};

	canCrit = false;

	baseDuration = 500;
	timePerTick = 100;
	maxStacks = 1;
	multiplyStatModsByStack = false; // if true, multiply stat mod by number of stacks.
	hasTicks = false;
	fixedDuration = false; // if true, ignore VIT in calculations
	unlimitedDuration = false;
	consumedOnUse = false; // if true, aura will expire when called in combat calculations
	isBuff = false;

	isStun = false;
	isDisarm = false;
	isSilence = false;
	isSlow = true;

	uniquePerActor = true; // determines if one actor can apply multiple copies of aura
	uniqueAura = true; // if true only one copy can be applied regardless of source

	removeAllStacksOnExpiration = false; // Determines whether all stacks or 1 stack are removed when aura expires
}

std::string Au_Icicle::GetDescription() {
	return "Reduces movement speed by 20%.";
}