// ==================================
//
// ab_attack.cpp
//
// ==================================

#include "../header/ab_attack.h"

#include "../../../entity/actor.h"

Ab_Attack::Ab_Attack() {
	setAttackDefault();

	name = "Attack";
	abilityID = AbilityID::ATTACK;
	icon = "attack.png";

	abilityTypes = {
		AbilityType::AXE_SKILL,
		AbilityType::BOW_SKILL,
		AbilityType::CLAW_SKILL,
		AbilityType::DAGGER_SKILL,
		AbilityType::MACE_SKILL,
		AbilityType::SPEAR_SKILL,
		AbilityType::STAFF_SKILL,
		AbilityType::SWORD_SKILL,
		AbilityType::WAND_SKILL
	};
	tier = 1;

	categories = { 
		Category::ATTACK,
		Category::DAMAGING,
		Category::SINGLE_TARGET,
		Category::DIRECT
	};

	requireTargetsInArea = true;
}

std::vector<sf::Vector3i> Ab_Attack::GetTargetArea(sf::Vector3i selectedTile) {
	std::vector<sf::Vector3i> tiles = { selectedTile };
	return tiles;
}

std::string Ab_Attack::GetDescription() {
	std::string damage = "100%";
	std::string damageOffHand = "";
	std::string desc = "Attack the target";

	if (user != nullptr) {
		damage = std::to_string(Combat::WeaponAttackEstimate(user, 1.0, false, abilityOptions));
		
		if (user->IsDualWielding()) {
			damageOffHand = std::to_string(Combat::WeaponAttackEstimate(user, 1.0, true, abilityOptions));
			desc += " with both weapons, dealing\n#damage " + damage + " #default weapon damage with your main hand and\n#damage " + damageOffHand + " #default weapon damage with your off-hand.";
			return desc;
		}
	}
	
	desc += ", dealing #damage " + damage + " #default weapon damage.";
	/*
	desc += "\n\n";
	desc += "#magic Linen Armor\n";
	desc += "#rare Refined Iron Spear\n";
	desc += "#mythic Dragonite Ring\n";
	desc += "#unique Sword of the Fallen Kingdom\n";
	desc += "#relic Shard of the Dragon Star";
	*/

	return desc;
}

void Ab_Attack::execute(std::vector<ActorPtr>& targets, sf::Vector3i cursor,std::vector<sf::Vector3i> targetArea) {
	Combat::WeaponAttack(user, targets[0], 1.0, false, abilityOptions);
	Combat::WeaponAttack(user, targets[0], offHandBasicMultiplier, true, abilityOptions);
}