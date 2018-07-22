// ==================================
//
// ab_fireNova.cpp
//
// ==================================

#include "../header/ab_fireNova.h"

#include "../../id/abilityID.h"
#include "../../id/abilityType.h"
#include "../../id/attribute.h"
#include "../../id/category.h"
#include "../../id/element.h"
#include "../../../hex/hexMath.h"
#include "../../../entity/actor.h"
#include "../../../hex/hexMath.h"

Ab_FireNova::Ab_FireNova() {
	setHarmfulSpellDefault();

	name = "Fire Nova";
	abilityID = AbilityID::FireNova;
	icon = "fire_nova.png";

	abilityTypes = {
		AbilityType::FireSpell
	};
	tier = 1;

	categories = {
		Category::Damaging,
		Category::AreaOfEffect,
		Category::Direct,
		Category::Spell
	};

	elements = { Element::Fire };

	castTime = 100;
	range = 1;
	aiSearchRange = 1;
	mpCost = 25;
	cooldown = 1000;

	targetOutsideCursor = true;

	requireTargetsInArea = true;
	isGroundTargeted = false;

	usage = UseType::Instant;
}

std::vector<sf::Vector3i> Ab_FireNova::GetTargetArea(sf::Vector3i selectedTile) {
	std::vector<sf::Vector3i> area = Hex::GetHexNeighbors(user->GetHexPosition(), 1);
	return area;
}

std::string Ab_FireNova::GetDescription() {
	std::string damage = "33";

	if (user != nullptr) {
		damage = std::to_string(Combat::ScalingAttackEstimate(user, 33.0, Attribute::INT, abilityOptions));
	}

	std::string desc = "Erupt with fire, dealing #damage " + damage + " #default fire damage to adjacent enemies.";
	desc = WordWrap::WrapString(desc, charPerLine);

	return desc;
}

void Ab_FireNova::execute(std::vector<ActorPtr>& targets, sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea) {
	for (size_t i = 0; i < targets.size(); i++) {
		Combat::ScalingAttack(user, targets[i], 33.0, Attribute::INT, abilityOptions);
	}
}