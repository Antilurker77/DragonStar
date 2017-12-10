// ==================================
//
// ab_heal.cpp
//
// ==================================

#include "../header/ab_heal.h"

Ab_Heal::Ab_Heal() {
	setHelpfulSpellDefault();

	name = "Heal";
	abilityID = AbilityID::HEAL;
	icon = "heal.png";

	abilityTypes = {
		AbilityType::DIVINE_HEAL
	};
	tier = 1;

	categories = {
		Category::DIRECT,
		Category::HEALING,
		Category::SINGLE_TARGET,
		Category::SPELL
	};

	elements = { Element::DIVINE_HEAL };

	castTime = 250;
	range = 5;
	aiSearchRange = range;
	mpCost = 25;

	usage = UseType::CAST;
}

std::vector<sf::Vector3i> Ab_Heal::GetTargetArea(sf::Vector3i selectedTile) {
	std::vector<sf::Vector3i> area = { selectedTile };
	return area;
}

std::string Ab_Heal::GetDescription() {
	std::string healing = "50";

	if (user != nullptr) {
		healing = std::to_string(Combat::ScalingHealEstimate(user, 50.0, Attribute::HP, abilityOptions));
	}

	std::string desc = "Heal and ally with divine light, restoring #heal " + healing + " #default HP.";

	return desc;
}

void Ab_Heal::execute(std::vector<ActorPtr>& targets, sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea) {
	Combat::ScalingHeal(user, targets[0], 50.0, Attribute::HP, abilityOptions);
}