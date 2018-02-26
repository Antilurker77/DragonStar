// ==================================
//
// ab_powerStrike.cpp
//
// ==================================

#include "../header/ab_powerStrike.h"

#include "../../id/abilityID.h"
#include "../../id/abilityType.h"
#include "../../id/attribute.h"
#include "../../id/auraID.h"
#include "../../id/category.h"
#include "../../id/element.h"
#include "../../id/equipType.h"

Ab_PowerStrike::Ab_PowerStrike() {
	setAttackDefault();

	name = "Power Strike";
	abilityID = AbilityID::POWER_STRIKE;
	icon = "power_strike.png";

	abilityTypes = {
		AbilityType::AXE_SKILL,
		AbilityType::CLAW_SKILL,
		AbilityType::DAGGER_SKILL,
		AbilityType::MACE_SKILL,
		AbilityType::SPEAR_SKILL,
		AbilityType::SWORD_SKILL
	};
	tier = 1;

	categories = {
		Category::ATTACK,
		Category::DAMAGING,
		Category::SINGLE_TARGET,
		Category::DIRECT
	};

	usableWeapons = {
		EquipType::SWORD_1H,
		EquipType::SWORD_2H,
		EquipType::AXE_1H,
		EquipType::AXE_2H,
		EquipType::MACE_1H,
		EquipType::MACE_2H,
		EquipType::DAGGER,
		EquipType::CLAW,
		EquipType::SPEAR
	};

	spCost = 20;
	cooldown = 800;

	usage = UseType::INSTANT;

	requireTargetsInArea = true;
}

std::vector<sf::Vector3i> Ab_PowerStrike::GetTargetArea(sf::Vector3i selectedTile) {
	std::vector<sf::Vector3i> tiles = { selectedTile };
	return tiles;
}

std::string Ab_PowerStrike::GetDescription() {
	std::string damage = "200%";

	if (user != nullptr) {
		damage = std::to_string(Combat::WeaponAttackEstimate(user, 2.0, false, abilityOptions));
	}

	std::string desc = "Deal a powerful strike against the target,\ndealing #damage " + damage + " #default weapon damage.";
	desc += "\n\nRequires melee weapon (except staff).";

	return desc;
}

void Ab_PowerStrike::execute(std::vector<ActorPtr>& targets, sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea) {
	Combat::WeaponAttack(user, targets[0], 2.0, false, abilityOptions);
	Combat::WeaponAttack(user, targets[0], offHandBasicMultiplier, true, abilityOptions);
}