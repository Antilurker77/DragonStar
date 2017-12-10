// ==================================
//
// au_healingRain.cpp
//
// ==================================

#include "../header/au_healingRain.h"

Au_HealingRain::Au_HealingRain() {
	name = "Healing Rain";
	id = AuraID::HEALING_RAIN;
	icon = "healing_rain.png";

	categories = {
		Category::HEALING,
		Category::OVER_TIME,
		Category::SINGLE_TARGET,
		Category::SPELL
	};

	elements = {
		Element::NATURE_HEAL
	};

	// debug
	//statMods = { StatMod(StatModType::DAMAGE, 123.45) };

	canCrit = true;

	baseDuration = 2000;
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

std::string Au_HealingRain::GetDescription() {
	std::string heal = "3";

	if (user != nullptr) {
		heal = std::to_string(Combat::ScalingHealEstimate(user, 3.0 * snapshotPower, Attribute::HP, auraOptions));
	}

	return "Heals #heal " + heal + " #default HP every 1s.";
}

void Au_HealingRain::OnTick() {
	double heal = 3.0 * nextTickPower * snapshotPower;
	Combat::ScalingHeal(user, target, heal, Attribute::HP, auraOptions);
}