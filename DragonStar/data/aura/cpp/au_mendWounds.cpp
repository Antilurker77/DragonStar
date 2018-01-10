// ==================================
//
// au_mendWounds.cpp
//
// ==================================

#include "../header/au_mendWounds.h"

#include "../../id/abilityID.h"
#include "../../id/attribute.h"
#include "../../id/auraID.h"
#include "../../id/category.h"
#include "../../id/element.h"
#include "../../id/statModType.h"

Au_MendWounds::Au_MendWounds() {
	name = "Mend Wounds";
	id = AuraID::MEND_WOUNDS;
	icon = "mend_wounds.png";

	categories = {
		Category::HEALING,
		Category::OVER_TIME,
		Category::SINGLE_TARGET,
		Category::SPELL
	};

	elements = {
		Element::NATURE_HEAL
	};

	canCrit = true;

	baseDuration = 400;
	timePerTick = 100;
	maxStacks = 1;
	hasTicks = true;
	fixedDuration = false; // if true, ignore VIT in calculations
	unlimitedDuration = false;
	consumedOnUse = false; // if true, aura will expire when called in combat calculations
	isBuff = true;

	isStun = false;
	isDisarm = false;
	isSilence = false;
	isSlow = false;

	uniquePerActor = true; // determines if one actor can apply multiple copies of aura
	uniqueAura = false; // if true only one copy can be applied regardless of source

	removeAllStacksOnExpiration = false; // Determines whether all stacks or 1 stack are removed when aura expires
}

std::string Au_MendWounds::GetDescription() {
	std::string heal = "10";

	if (user != nullptr) {
		heal = std::to_string(Combat::ScalingHealEstimate(user, 10.0 * snapshotPower, Attribute::HP, auraOptions));
	}

	return "Heals #heal " + heal + " #default HP every 1s.";
}

void Au_MendWounds::OnTick() {
	double heal = 10.0 * nextTickPower * snapshotPower;
	Combat::ScalingHeal(user, target, heal, Attribute::HP, auraOptions);
}

void Au_MendWounds::OnExpiry() {

}