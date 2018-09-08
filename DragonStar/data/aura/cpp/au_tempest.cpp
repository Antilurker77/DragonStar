// ==================================
//
// au_tempest.cpp
//
// ==================================

#include "../header/au_tempest.h"

#include "../../id/abilityID.h"
#include "../../id/attribute.h"
#include "../../id/auraID.h"
#include "../../id/category.h"
#include "../../id/element.h"
#include "../../id/statModType.h"

Au_Tempest::Au_Tempest() {
	name = "Tempest";
	id = AuraID::Tempest;
	icon = "tempest.png";

	categories = {
		Category::AreaOfEffect,
		Category::Attack,
		Category::Skill
	};

	elements = {
		Element::Lightning,
		Element::Water,
		Element::Wind
	};

	statMods = {
		StatMod(StatModType::DamageTaken, 0.10,{ Category::Any },{ Element::Lightning, Element::Water, Element::Wind })
	};

	canCrit = false;

	baseDuration = 1200;
	timePerTick = 0;
	maxStacks = 1;
	hasTicks = false;
	fixedDuration = false; // if true, ignore VIT in calculations
	unlimitedDuration = false;
	consumedOnUse = false; // if true, aura will expire when called in combat calculations

	isStun = false;
	isDisarm = false;
	isSilence = false;
	isSlow = false;

	uniquePerActor = true; // determines if one actor can apply multiple copies of aura
	uniqueAura = true; // if true only one copy can be applied regardless of source

	removeAllStacksOnExpiration = false; // Determines whether all stacks or 1 stack are removed when aura expires
}

std::string Au_Tempest::GetDescription() {
	return "Increases lightning, water, and wind damage\ntaken by 10%.";
}