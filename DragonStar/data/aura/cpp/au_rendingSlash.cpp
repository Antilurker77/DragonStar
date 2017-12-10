// ==================================
//
// au_rendingSlash.cpp
//
// ==================================

#include "../header/au_rendingSlash.h"

Au_RendingSlash::Au_RendingSlash() {
	name = "Rending Slash";
	id = AuraID::RENDING_SLASH;
	icon = "rending_slash.png";

	categories = {
		Category::DAMAGING,
		Category::OVER_TIME,
		Category::SINGLE_TARGET,
		Category::ATTACK
	};

	elements = {
		Element::PHYSICAL
	};

	canCrit = true;

	baseDuration = 1000;
	timePerTick = 100;
	maxStacks = 1;
	hasTicks = true;
	fixedDuration = false; // if true, ignore VIT in calculations
	unlimitedDuration = false;
	consumedOnUse = false; // if true, aura will expire when called in combat calculations

	isStun = false;
	isDisarm = false;
	isSilence = false;
	isSlow = false;

	uniquePerActor = true; // determines if one actor can apply multiple copies of aura
	uniqueAura = false; // if true only one copy can be applied regardless of source

	removeAllStacksOnExpiration = false; // Determines whether all stacks or 1 stack are removed when aura expires
}

std::string Au_RendingSlash::GetDescription() {
	std::string damage = "15%";

	if (user != nullptr) {
		damage = std::to_string(Combat::WeaponAttackEstimate(user, 0.15, false, auraOptions));
	}

	return "Deals #damage " + damage + " #default physical damage every 1s.";

}

void Au_RendingSlash::OnTick() {
	double multiplier = 0.15 * nextTickPower * snapshotPower;
	Combat::WeaponAttack(user, target, multiplier, false, auraOptions);
}