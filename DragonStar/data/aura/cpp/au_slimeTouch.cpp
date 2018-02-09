// ==================================
//
// au_slimeTouch.cpp
//
// ==================================

#include "../header/au_slimeTouch.h"

#include "../../id/abilityID.h"
#include "../../id/attribute.h"
#include "../../id/auraID.h"
#include "../../id/category.h"
#include "../../id/element.h"
#include "../../id/statModType.h"

Au_SlimeTouch::Au_SlimeTouch() {
	name = "Slime Touch";
	id = AuraID::SLIME_TOUCH;
	icon = "slime_touch.png";

	categories = {
		Category::SKILL
	};

	elements = {
		Element::WATER
	};

	statMods = {
		StatMod(StatModType::HASTE, -0.03),
		StatMod(StatModType::MOVEMENT_SPEED, -0.03)
	};

	canCrit = false;

	baseDuration = 500;
	timePerTick = 0;
	maxStacks = 10;
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

	removeAllStacksOnExpiration = true; // Determines whether all stacks or 1 stack are removed when aura expires
	multiplyStatModsByStack = true;
}

std::string Au_SlimeTouch::GetDescription() {
	std::string amount = std::to_string(3 * stackCount);
	std::string desc = "Reduces haste by " + amount + "%.\nReduces movement speed by " + amount + "%.";
	return desc;
}