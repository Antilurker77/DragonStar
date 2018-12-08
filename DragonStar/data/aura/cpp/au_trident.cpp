// ==================================
//
// au_trident.cpp
//
// ==================================

#include "../header/au_trident.h"

#include "../../id/abilityID.h"
#include "../../id/attribute.h"
#include "../../id/auraID.h"
#include "../../id/category.h"
#include "../../id/element.h"
#include "../../id/statModType.h"

Au_Trident::Au_Trident() {
	name = "Trident";
	id = AuraID::Trident;
	icon = "trident.png";

	categories = {
		Category::Skill,
		Category::Damaging
	};

	elements = {
		Element::Water
	};

	statMods = {
		StatMod(StatModType::Damage, 0.30, { Category::Any }, { Element::Water })
	};

	canCrit = false;

	baseDuration = 2000;
	timePerTick = 0;
	maxStacks = 1;
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

void Au_Trident::OnEvent(EventType eventType, ActorPtr& target, BattleScene* battleScene, EventOptions& eventOptions, EventResult& eventResult, bool isOffHand, double& amount) {
	// OnAttack
	if (eventType == EventType::Attack) {
		auto c = eventOptions.Categories;
		if (std::find(c.begin(), c.end(), Category::Direct) != c.end()) {
			Combat::ScalingAttack(user, target, 25.0, Attribute::DEX, auraOptions);
		}
	}
}

std::string Au_Trident::GetDescription() {
	std::string damage = "25";

	if (user != nullptr) {
		damage = std::to_string(Combat::ScalingAttackEstimate(user, 25.0, Attribute::DEX, auraOptions));
	}

	std::string desc = "Increases water damage dealt by 30%.\n";
	desc += "Attacks deal #damage " + damage + " #default water damage on hit.";
	return desc;
}