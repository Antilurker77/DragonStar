// ==================================
//
// ab_mendingWaters.cpp
//
// ==================================

#include "../header/ab_mendingWaters.h"

#include "../../id/abilityID.h"
#include "../../id/abilityType.h"
#include "../../id/attribute.h"
#include "../../id/auraID.h"
#include "../../id/category.h"
#include "../../id/element.h"

Ab_MendingWaters::Ab_MendingWaters() {
	setHelpfulSpellDefault();

	name = "Mending Waters";
	abilityID = AbilityID::MendingWaters;
	icon = "mending_waters.png";

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

	castTime = 150;
	range = 5;
	aiSearchRange = range;
	mpCost = 25;

	usage = UseType::Cast;
}

std::vector<sf::Vector3i> Ab_MendingWaters::GetTargetArea(sf::Vector3i selectedTile) {
	std::vector<sf::Vector3i> area = { selectedTile };
	return area;
}

std::string Ab_MendingWaters::GetDescription() {
	std::string heal = "8";

	if (user != nullptr) {
		heal = std::to_string(Combat::ScalingHealEstimate(user, 8.0, Attribute::HP, abilityOptions));
	}

	std::string desc = "Heal an ally with mending waters, restoring #heal " + heal + " #default HP every 1s for 12s.";
	desc = WordWrap::WrapString(desc, charPerLine);

	return desc;
}

void Ab_MendingWaters::execute(std::vector<ActorPtr>& targets, sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea) {
	Combat::AddAuraStack(user, targets[0], AuraID::MendingWaters);
}