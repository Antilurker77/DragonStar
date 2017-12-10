// ==================================
//
// ab_flameBolt.cpp
//
// ==================================

#include "../header/ab_flameBolt.h"

Ab_FlameBolt::Ab_FlameBolt() {
	setHarmfulSpellDefault();

	name = "Flame Bolt";
	abilityID = AbilityID::FLAME_BOLT;
	icon = "flame_bolt.png";

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
	mpCost = 12;

	requireTargetsInArea = true;
	isGroundTargeted = false;

	usage = UseType::CAST;
}

std::vector<sf::Vector3i> Ab_FlameBolt::GetTargetArea(sf::Vector3i selectedTile) {
	std::vector<sf::Vector3i> area = { selectedTile };
	return area;
}

std::string Ab_FlameBolt::GetDescription() {
	std::string damage = "35";

	if (user != nullptr) {
		damage = std::to_string(Combat::ScalingAttackEstimate(user, 35.0, Attribute::INT, abilityOptions));
	}

	std::string desc = "Shoot a bolt of fire at the target, dealing\n#damage " + damage + " #default fire damage.";
	return desc;
}

void Ab_FlameBolt::execute(std::vector<ActorPtr>& targets, sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea) {
	Combat::ScalingAttack(user, targets[0], 35.0, Attribute::INT, abilityOptions);
}