// ==================================
//
// ab_rendingSlash.cpp
//
// ==================================

#include "../header/ab_rendingSlash.h"

Ab_RendingSlash::Ab_RendingSlash() {
	setAttackDefault();

	name = "Rending Slash";
	abilityID = AbilityID::RENDING_SLASH;
	icon = "rending_slash.png";

	abilityTypes = {
		AbilityType::AXE_SKILL,
		AbilityType::CLAW_SKILL,
		AbilityType::DAGGER_SKILL,
		AbilityType::SWORD_SKILL
	};
	tier = 1;

	categories = {
		Category::ATTACK,
		Category::DAMAGING,
		Category::SINGLE_TARGET,
		Category::DIRECT
	};

	spCost = 25;
	cooldown = 2000;

	usage = UseType::INSTANT;

	requireTargetsInArea = true;
}

std::vector<sf::Vector3i> Ab_RendingSlash::GetTargetArea(sf::Vector3i selectedTile) {
	std::vector<sf::Vector3i> tiles = { selectedTile };
	return tiles;
}

std::string Ab_RendingSlash::GetDescription() {
	std::string damage = "110%";
	std::string dotDamage = "15%";

	if (user != nullptr) {
		damage = std::to_string(Combat::WeaponAttackEstimate(user, 1.1, false, abilityOptions));
		dotDamage = std::to_string(Combat::WeaponAttackEstimate(user, 0.15, false, abilityOptions));
	}

	std::string desc = "Slash the target, dealing #damage " + damage + " #default weapon damage plus\n#damage " + dotDamage + " #default physical damage every 1s for 10s.";

	return desc;
}

void Ab_RendingSlash::execute(std::vector<ActorPtr>& targets, sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea) {
	auto result = Combat::WeaponAttack(user, targets[0], 1.1, false, abilityOptions);
	if (result.DidHit) {
		Combat::AddAuraStack(user, targets[0], AuraID::RENDING_SLASH);
	}
	Combat::WeaponAttack(user, targets[0], offHandBasicMultiplier, true, abilityOptions);
}