// ==================================
//
// ab_dragonfireBolt.cpp
//
// ==================================

#include "../header/ab_dragonfireBolt.h"

Ab_DragonfireBolt::Ab_DragonfireBolt() {
	setHarmfulSpellDefault();

	name = "Dragonfire Bolt";
	abilityID = AbilityID::DRAGONFIRE_BOLT;
	icon = "dragonfire_bolt.png";

	abilityTypes = {
		AbilityType::FIRE_SPELL
	};
	tier = 1;

	categories = {
		Category::DAMAGING,
		Category::SINGLE_TARGET,
		Category::DIRECT,
		Category::SPELL
	};

	elements = { Element::FIRE };

	castTime = 200;
	range = 4;
	aiSearchRange = range;
	mpCost = 25;
	cooldown = 1200;

	requireTargetsInArea = true;
	isGroundTargeted = false;

	usage = UseType::CAST;
}

std::vector<sf::Vector3i> Ab_DragonfireBolt::GetTargetArea(sf::Vector3i selectedTile) {
	std::vector<sf::Vector3i> area = { selectedTile };
	return area;
}

std::string Ab_DragonfireBolt::GetDescription() {
	std::string damage = "63";

	if (user != nullptr) {
		damage = std::to_string(Combat::ScalingAttackEstimate(user, 63.0, Attribute::INT, abilityOptions));
	}

	std::string desc = "Shoot a bolt of draconic flames at the target, dealing\n#damage " + damage + " #default fire damage.";
	return desc;
}

void Ab_DragonfireBolt::execute(std::vector<ActorPtr>& targets, sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea) {
	Combat::ScalingAttack(user, targets[0], 63.0, Attribute::INT, abilityOptions);
}