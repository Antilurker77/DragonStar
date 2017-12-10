// ==================================
//
// ab_gale.cpp
//
// ==================================

#include "../header/ab_gale.h"

Ab_Gale::Ab_Gale() {
	setHarmfulSpellDefault();

	name = "Gale";
	abilityID = AbilityID::GALE;
	icon = "gale.png";

	abilityTypes = {
		AbilityType::WIND_SPELL
	};
	tier = 1;

	categories = {
		Category::DAMAGING,
		Category::SINGLE_TARGET,
		Category::DIRECT,
		Category::SPELL
	};

	elements = { Element::WIND };

	castTime = 200;
	range = 4;
	aiSearchRange = range;
	mpCost = 10;

	requireTargetsInArea = true;
	isGroundTargeted = false;

	usage = UseType::CAST;
}

std::vector<sf::Vector3i> Ab_Gale::GetTargetArea(sf::Vector3i selectedTile) {
	std::vector<sf::Vector3i> area = { selectedTile };
	return area;
}

std::string Ab_Gale::GetDescription() {
	std::string damage = "18";

	if (user != nullptr) {
		damage = std::to_string(Combat::ScalingAttackEstimate(user, 18.0, Attribute::INT, abilityOptions));
	}

	std::string desc = "Launch a slicing gale at the target,\ndealing #damage " + damage + " #default wind damage. Reduces the cast\ntime of Gale by 0.1s. Stacks up to 5\ntimes and lasts 5s.";
	return desc;
}

void Ab_Gale::execute(std::vector<ActorPtr>& targets, sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea) {
	auto result = Combat::ScalingAttack(user, targets[0], 18.0, Attribute::INT, abilityOptions);
	Combat::AddAuraStack(user, user, AuraID::GALE);
}