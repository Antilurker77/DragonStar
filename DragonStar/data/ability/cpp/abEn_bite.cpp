// ==================================
//
// abEn_bite.cpp
//
// ==================================

#include "../header/abEn_bite.h"

#include "../../id/abilityID.h"
#include "../../id/abilityType.h"
#include "../../id/category.h"
#include "../../id/element.h"

AbEn_Bite::AbEn_Bite() {
	setAttackDefault();

	name = "Bite";
	abilityID = AbilityID::EN_BITE;
	icon = "strength.png";

	abilityTypes = {
		AbilityType::UNARMED_SKILL
	};
	tier = 1;

	categories = {
		Category::ATTACK,
		Category::DAMAGING,
		Category::SINGLE_TARGET,
		Category::DIRECT
	};

	spCost = 40;
	cooldown = 450;

	usage = UseType::INSTANT;

	requireTargetsInArea = true;
}

std::vector<sf::Vector3i> AbEn_Bite::GetTargetArea(sf::Vector3i selectedTile) {
	std::vector<sf::Vector3i> tiles = { selectedTile };
	return tiles;
}

std::string AbEn_Bite::GetDescription() {
	std::string damage = "150%";

	if (user != nullptr) {
		damage = std::to_string(Combat::WeaponAttackEstimate(user, 1.5, false, abilityOptions));
	}

	std::string desc = "Deals #damage " + damage + " #default weapon damage.";

	return desc;
}

void AbEn_Bite::execute(std::vector<ActorPtr>& targets, sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea) {
	Combat::WeaponAttack(user, targets[0], 1.5, false, abilityOptions);
	Combat::WeaponAttack(user, targets[0], offHandBasicMultiplier, true, abilityOptions);
}