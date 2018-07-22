// ==================================
//
// ab_chopper.cpp
//
// ==================================

#include "../header/ab_chopper.h"

#include "../../id/abilityID.h"
#include "../../id/abilityType.h"
#include "../../id/attribute.h"
#include "../../id/auraID.h"
#include "../../id/category.h"
#include "../../id/element.h"
#include "../../id/equipType.h"

Ab_Chopper::Ab_Chopper() {
	setAttackDefault();

	name = "Chopper";
	abilityID = AbilityID::Chopper;
	icon = "chopper.png";

	abilityTypes = {
		AbilityType::AxeSkill
	};
	tier = 1;

	categories = {
		Category::Attack,
		Category::Skill,
		Category::Damaging,
		Category::SingleTarget,
		Category::Direct
	};

	usableWeapons = {
		EquipType::Axe1H,
		EquipType::Axe2H
	};

	spCost = 35;
	cooldown = 1000;

	usage = UseType::Instant;

	requireTargetsInArea = true;

	bonusDoubleStrike = 0.5;
}

std::vector<sf::Vector3i> Ab_Chopper::GetTargetArea(sf::Vector3i selectedTile) {
	std::vector<sf::Vector3i> tiles = { selectedTile };
	return tiles;
}

std::string Ab_Chopper::GetDescription() {
	std::string damage = "175%";

	if (user != nullptr) {
		damage = std::to_string(Combat::WeaponAttackEstimate(user, 1.75, false, abilityOptions));
	}

	std::string desc = "Strike the enemy with your axe, dealing #damage " + damage + " #default weapon damage. Chopper has a 50% increased chance to double strike.";
	desc = WordWrap::WrapString(desc, charPerLine);

	desc += "\n\nRequires axe.";

	return desc;
}

void Ab_Chopper::execute(std::vector<ActorPtr>& targets, sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea) {
	Combat::WeaponAttack(user, targets[0], 1.75, false, abilityOptions);
	Combat::WeaponAttack(user, targets[0], offHandBasicMultiplier, true, abilityOptions);
}