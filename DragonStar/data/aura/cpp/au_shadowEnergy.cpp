// ==================================
//
// au_shadowEnergy.cpp
//
// ==================================

#include "../header/au_shadowEnergy.h"

#include "../../id/abilityID.h"
#include "../../id/attribute.h"
#include "../../id/auraID.h"
#include "../../id/category.h"
#include "../../id/element.h"
#include "../../id/statModType.h"

Au_ShadowEnergy::Au_ShadowEnergy() {
	name = "Shadow Energy";
	id = AuraID::ShadowEnergy;
	icon = "dark_bolt.png";

	categories = {
		Category::Spell,
		Category::Damaging
	};

	elements = {
		Element::Dark
	};

	statMods = {

	};

	canCrit = false;

	baseDuration = 0;
	timePerTick = 0;
	maxStacks = 1;
	hasTicks = false;
	fixedDuration = false; // if true, ignore VIT in calculations
	unlimitedDuration = true;
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

void Au_ShadowEnergy::OnEvent(EventType eventType, ActorPtr& target, BattleScene* battleScene, EventOptions& eventOptions, EventResult& eventResult, bool isOffHand, double& amount) {
	// OnAttack
	if (eventType == EventType::Attack) {
		auto c = eventOptions.Categories;
		if (std::find(c.begin(), c.end(), Category::Direct) != c.end()) {
			Combat::ScalingAttack(user, target, 20.0, Attribute::INT, auraOptions);
		}
	}
}

std::string Au_ShadowEnergy::GetDescription() {
	std::string damage = "20";

	if (user != nullptr) {
		damage = std::to_string(Combat::ScalingAttackEstimate(user, 20.0, Attribute::INT, auraOptions));
	}

	std::string desc = "Attacks deal #damage " + damage + " #default dark damage on hit.";
	return desc;
}