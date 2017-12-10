// ==================================
//
// venom.cpp
//
// ==================================

#include "../header/ab_venom.h"

Ab_Venom::Ab_Venom() {
	setHarmfulSpellDefault();

	name = "Venom";
	abilityID = AbilityID::VENOM;
	icon = "venom.png";

	abilityTypes = {
		AbilityType::POISON_SPELL
	};
	tier = 1;

	categories = {
		Category::DAMAGING,
		Category::SINGLE_TARGET,
		Category::DIRECT,
		Category::SPELL
	};

	elements = { Element::POISON };

	castTime = 200;
	range = 4;
	aiSearchRange = range;
	mpCost = 15;

	requireTargetsInArea = true;
	isGroundTargeted = false;

	usage = UseType::CAST;
}

std::vector<sf::Vector3i> Ab_Venom::GetTargetArea(sf::Vector3i selectedTile) {
	std::vector<sf::Vector3i> area = { selectedTile };
	return area;
}

std::string Ab_Venom::GetDescription() {
	std::string mainDamage = "9";
	std::string dotDamage = "3";

	if (user != nullptr) {
		mainDamage = std::to_string(Combat::ScalingAttackEstimate(user, 9.0, Attribute::INT, abilityOptions));
		dotDamage = std::to_string(Combat::ScalingAttackEstimate(user, 3.0, Attribute::INT, abilityOptions));
	}

	std::string desc = "Lob a ball of venom at the target, dealing #damage " + mainDamage +
		" #default poison\ndamage and an additional #damage " + dotDamage + " #default poison damage every 1s\nfor 16s.";

	return desc;
}

void Ab_Venom::execute(std::vector<ActorPtr>& targets, sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea) {
	Combat::ScalingAttack(user, targets[0], 9.0, Attribute::INT, abilityOptions);
	Combat::AddAuraStack(user, targets[0], AuraID::VENOM);
}