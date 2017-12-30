// ==================================
//
// ab_icicle.cpp
//
// ==================================

#include "../header/ab_icicle.h"

Ab_Icicle::Ab_Icicle() {
	setHarmfulSpellDefault();

	name = "Icicle";
	abilityID = AbilityID::ICICLE;
	icon = "icicle.png";

	abilityTypes = {
		AbilityType::ICE_SPELL
	};
	tier = 1;

	categories = {
		Category::DAMAGING,
		Category::SINGLE_TARGET,
		Category::DIRECT,
		Category::SPELL
	};

	elements = { Element::ICE };

	castTime = 200;
	range = 4;
	aiSearchRange = range;
	mpCost = 10;

	requireTargetsInArea = true;
	isGroundTargeted = false;

	usage = UseType::CAST;
}

std::vector<sf::Vector3i> Ab_Icicle::GetTargetArea(sf::Vector3i selectedTile) {
	std::vector<sf::Vector3i> area = { selectedTile };
	return area;
}

std::string Ab_Icicle::GetDescription() {
	std::string damage = "38";

	if (user != nullptr) {
		damage = std::to_string(Combat::ScalingAttackEstimate(user, 38.0, Attribute::INT, abilityOptions));
	}

	std::string desc = "Hurl an icicle at the target, dealing\n#damage " + damage + " #default ice damage and reducing the target's\nmovement speed by 20% for 5s.";
	return desc;
}

void Ab_Icicle::execute(std::vector<ActorPtr>& targets, sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea) {
	auto result = Combat::ScalingAttack(user, targets[0], 38.0, Attribute::INT, abilityOptions);
	if (result.DidHit) {
		Combat::AddAuraStack(user, targets[0], AuraID::ICICLE);
	}
}