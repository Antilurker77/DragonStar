// ==================================
//
// au_venom.cpp
//
// ==================================

#include "../header/au_venom.h"

#include "../../id/abilityID.h"
#include "../../id/attribute.h"
#include "../../id/auraID.h"
#include "../../id/category.h"
#include "../../id/element.h"
#include "../../id/statModType.h"

Au_Venom::Au_Venom() {
	name = "Venom";
	id = AuraID::Venom;
	icon = "venom.png";

	categories = {
		Category::Damaging,
		Category::OverTime,
		Category::SingleTarget,
		Category::Spell
	};

	elements = {
		Element::Poison
	};

	canCrit = true;

	baseDuration = 1600;
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

std::string Au_Venom::GetDescription() {
	std::string damage = "5";

	if (user != nullptr) {
		damage = std::to_string(Combat::ScalingAttackEstimate(user, 5.0 * snapshotPower, Attribute::INT, auraOptions));
	}

	return "Deals #damage " + damage + " #default poison damage every 1s.";

}

void Au_Venom::OnTick() {
	double dmg = 5.0 * nextTickPower * snapshotPower;
	Combat::ScalingAttack(user, target, dmg, Attribute::INT, auraOptions);
}

void Au_Venom::OnExpiry() {

}