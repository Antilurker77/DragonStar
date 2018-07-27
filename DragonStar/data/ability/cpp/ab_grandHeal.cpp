// ==================================
//
// ab_grandHeal.cpp
//
// ==================================

#include "../header/ab_grandHeal.h"

#include "../../id/abilityID.h"
#include "../../id/abilityType.h"
#include "../../id/attribute.h"
#include "../../id/category.h"
#include "../../id/element.h"
#include "../../../hex/hexMath.h"

Ab_GrandHeal::Ab_GrandHeal() {
	setHelpfulSpellDefault();

	name = "Grand Heal";
	abilityID = AbilityID::GrandHeal;
	icon = "grand_heal.png";

	abilityTypes = {
		AbilityType::DivineHeal
	};
	tier = 1;

	categories = {
		Category::Direct,
		Category::Healing,
		Category::SingleTarget,
		Category::Spell
	};

	elements = { Element::DivineHeal };

	castTime = 250;
	cooldown = 1500;
	range = 5;
	aiSearchRange = range;
	mpCost = 40;

	usage = UseType::Cast;
}

std::vector<sf::Vector3i> Ab_GrandHeal::GetTargetArea(sf::Vector3i selectedTile) {
	std::vector<sf::Vector3i> area = { selectedTile };
	return area;
}

std::string Ab_GrandHeal::GetDescription() {
	std::string healing = "150";

	if (user != nullptr) {
		healing = std::to_string(Combat::ScalingHealEstimate(user, 150.0, Attribute::HP, abilityOptions));
	}

	std::string desc = "Bathe an ally with divine light, restoring #heal " + healing + " #default HP.";
	desc = WordWrap::WrapString(desc, charPerLine);

	return desc;
}

void Ab_GrandHeal::execute(std::vector<ActorPtr>& targets, sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea) {
	Combat::ScalingHeal(user, targets[0], 150.0, Attribute::HP, abilityOptions);
}