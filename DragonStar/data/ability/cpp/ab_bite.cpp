// ==================================
//
// ab_bite.cpp
//
// ==================================

#include "../header/ab_bite.h"

#include "../../id/abilityID.h"
#include "../../id/abilityType.h"
#include "../../id/category.h"
#include "../../id/element.h"

Ab_Bite::Ab_Bite() {
	setAttackDefault();

	name = "Bite";
	abilityID = AbilityID::Bite;
	icon = "strength.png";

	abilityTypes = {
		AbilityType::UnarmedSkill
	};
	tier = 1;

	categories = {
		Category::Attack,
		Category::Damaging,
		Category::SingleTarget,
		Category::Direct
	};

	spCost = 40;
	cooldown = 450;

	usage = UseType::Instant;

	requireTargetsInArea = true;
}

std::vector<sf::Vector3i> Ab_Bite::GetTargetArea(sf::Vector3i selectedTile) {
	std::vector<sf::Vector3i> tiles = { selectedTile };
	return tiles;
}

std::string Ab_Bite::GetDescription() {
	std::string damage = "150%";

	if (user != nullptr) {
		damage = std::to_string(Combat::WeaponAttackEstimate(user, 1.5, false, abilityOptions));
	}

	std::string desc = "Deals #damage " + damage + " #default weapon damage.";
	desc = WordWrap::WrapString(desc, charPerLine);

	return desc;
}

void Ab_Bite::execute(std::vector<ActorPtr>& targets, sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea) {
	Combat::WeaponAttack(user, targets[0], 1.5, false, abilityOptions);
	Combat::WeaponAttack(user, targets[0], offHandBasicMultiplier, true, abilityOptions);
}