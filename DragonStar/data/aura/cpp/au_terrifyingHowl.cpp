// ==================================
//
// au_terrifyingHowl.cpp
//
// ==================================

#include "../header/au_terrifyingHowl.h"

#include "../../id/abilityID.h"
#include "../../id/attribute.h"
#include "../../id/auraID.h"
#include "../../id/category.h"
#include "../../id/element.h"
#include "../../id/statModType.h"

Au_TerrifyingHowl::Au_TerrifyingHowl() {
	name = "Terrifying Howl";
	id = AuraID::TerrifyingHowl;
	icon = "screech.png";

	categories = {
		Category::Skill
	};

	elements = {
		Element::Physical
	};

	statMods = {
		StatMod(StatModType::Damage, -0.2),
		StatMod(StatModType::HitChance, -0.2)
	};

	canCrit = false;

	baseDuration = 1000;
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

std::string Au_TerrifyingHowl::GetDescription() {
	return "Reduces damage dealt by 20%.\nReduces hit chance by 20%.";
}