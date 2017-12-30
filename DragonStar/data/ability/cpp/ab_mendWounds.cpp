// ==================================
//
// ab_mendWounds.cpp
//
// ==================================

#include "../header/ab_mendWounds.h"

Ab_MendWounds::Ab_MendWounds() {
	setHelpfulSpellDefault();

	name = "Mend Wounds";
	abilityID = AbilityID::MEND_WOUNDS;
	icon = "mend_wounds.png";

	abilityTypes = {
		AbilityType::NATURE_HEAL
	};
	tier = 1;

	categories = {
		Category::DIRECT,
		Category::HEALING,
		Category::SINGLE_TARGET,
		Category::SPELL
	};

	elements = { Element::NATURE_HEAL };

	castTime = 250;
	range = 5;
	aiSearchRange = range;
	mpCost = 25;

	usage = UseType::CAST;
}

std::vector<sf::Vector3i> Ab_MendWounds::GetTargetArea(sf::Vector3i selectedTile) {
	std::vector<sf::Vector3i> area = { selectedTile };
	return area;
}

std::string Ab_MendWounds::GetDescription() {
	std::string mainHeal = "60";
	std::string hotHeal = "10";

	if (user != nullptr) {
		mainHeal = std::to_string(Combat::ScalingHealEstimate(user, 60.0, Attribute::HP, abilityOptions));
		hotHeal = std::to_string(Combat::ScalingHealEstimate(user, 10.0, Attribute::HP, abilityOptions));
	}

	std::string desc = "Heal an ally with natural energies, restoring #heal " + mainHeal + " #default HP\nplus an additional #heal "
		+ hotHeal + " #default HP every 1s for 4s.";
	return desc;
}

void Ab_MendWounds::execute(std::vector<ActorPtr>& targets, sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea) {
	Combat::ScalingHeal(user, targets[0], 60.0, Attribute::HP, abilityOptions);
	Combat::AddAuraStack(user, targets[0], AuraID::MEND_WOUNDS);
}