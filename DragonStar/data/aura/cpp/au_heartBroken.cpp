// ==================================
//
// au_heartBroken.cpp
//
// ==================================

#include "../header/au_heartBroken.h"

#include "../../id/abilityID.h"
#include "../../id/attribute.h"
#include "../../id/auraID.h"
#include "../../id/category.h"
#include "../../id/element.h"
#include "../../id/statModType.h"

Au_HeartBroken::Au_HeartBroken() {
	name = "Heart Broken";
	id = AuraID::HeartBroken;
	icon = "heart_broken.png";

	categories = {
		Category::Skill
	};

	elements = {
		Element::Physical
	};

	statMods = {
		StatMod(StatModType::VIT, -25.0)
	};

	canCrit = false;

	baseDuration = 1500;
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

	removeAllStacksOnExpiration = true; // Determines whether all stacks or 1 stack are removed when aura expires
	multiplyStatModsByStack = false;
}

std::string Au_HeartBroken::GetDescription() {
	std::string desc = "Reduces VIT by 25.";
	return desc;
}