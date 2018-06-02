// ==================================
//
// ab_mendWounds.cpp
//
// ==================================

#include "../header/ab_mendWounds.h"

#include "../../id/abilityID.h"
#include "../../id/abilityType.h"
#include "../../id/attribute.h"
#include "../../id/auraID.h"
#include "../../id/category.h"
#include "../../id/element.h"

Ab_MendWounds::Ab_MendWounds() {
	setHelpfulSpellDefault();

	name = "Mend Wounds";
	abilityID = AbilityID::MendWounds;
	icon = "mend_wounds.png";

	abilityTypes = {
		AbilityType::NatureHeal
	};
	tier = 1;

	categories = {
		Category::Direct,
		Category::Healing,
		Category::SingleTarget,
		Category::Spell
	};

	elements = { Element::NatureHeal };

	castTime = 250;
	range = 5;
	aiSearchRange = range;
	mpCost = 25;

	usage = UseType::Cast;
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

	std::string desc = "Heal an ally with natural energies, restoring #heal " + mainHeal + " #default HP plus an additional #heal "
		+ hotHeal + " #default HP every 1s for 4s.";
	desc = WordWrap::WrapString(desc, 42);

	return desc;
}

void Ab_MendWounds::execute(std::vector<ActorPtr>& targets, sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea) {
	Combat::ScalingHeal(user, targets[0], 60.0, Attribute::HP, abilityOptions);
	Combat::AddAuraStack(user, targets[0], AuraID::MendWounds);
}