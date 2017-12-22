// ==================================
//
// ab_fireNova.cpp
//
// ==================================

#include "../header/ab_fireNova.h"

#include "../../../entity/actor.h"
#include "../../../hex/hexMath.h"

Ab_FireNova::Ab_FireNova() {
	setHarmfulSpellDefault();

	name = "Fire Nova";
	abilityID = AbilityID::FIRE_NOVA;
	icon = "fire_nova.png";

	abilityTypes = {
		AbilityType::FIRE_SPELL
	};
	tier = 1;

	categories = {
		Category::DAMAGING,
		Category::AREA_OF_EFFECT,
		Category::DIRECT,
		Category::SPELL
	};

	elements = { Element::FIRE };

	castTime = 100;
	range = 0;
	aiSearchRange = 1;
	mpCost = 25;
	cooldown = 1000;

	requireTargetsInArea = true;
	isGroundTargeted = false;

	usage = UseType::INSTANT;
}

std::vector<sf::Vector3i> Ab_FireNova::GetTargetArea(sf::Vector3i selectedTile) {
	std::vector<sf::Vector3i> area = Hex::GetHexNeighbors(user->GetHexPosition(), 1);
	return area;
}

std::string Ab_FireNova::GetDescription() {
	std::string damage = "20";

	if (user != nullptr) {
		damage = std::to_string(Combat::ScalingAttackEstimate(user, 20.0, Attribute::INT, abilityOptions));
	}

	std::string desc = "Erupt with fire, dealing #damage " + damage + " #default fire damage to adjacent\nenemies.";
	return desc;
}

void Ab_FireNova::execute(std::vector<ActorPtr>& targets, sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea) {
	for (size_t i = 0; i < targets.size(); i++) {
		Combat::ScalingAttack(user, targets[i], 20.0, Attribute::INT, abilityOptions);
	}
}