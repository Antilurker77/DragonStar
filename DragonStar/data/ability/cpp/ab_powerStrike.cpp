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
	abilityID = AbilityID::PowerStrike;
	icon = "power_strike.png";

	abilityTypes = {
		AbilityType::AxeSkill,
		AbilityType::ClawSkill,
		AbilityType::DaggerSkill,
		AbilityType::MaceSkill,
		AbilityType::SpearSkill,
		AbilityType::SwordSkill
	};
	tier = 1;

	categories = {
		Category::Attack,
		Category::Damaging,
		Category::SingleTarget,
		Category::Direct
	};

	usableWeapons = {
		EquipType::Sword1H,
		EquipType::Sword2H,
		EquipType::Axe1H,
		EquipType::Axe2H,
		EquipType::Mace1H,
		EquipType::Mace2H,
		EquipType::Dagger,
		EquipType::Claw,
		EquipType::Spear
	};

	spCost = 20;
	cooldown = 800;

	usage = UseType::Instant;

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

	std::string desc = "Deal a powerful strike against the target, dealing #damage " + damage + " #default weapon damage.";
	desc = WordWrap::WrapString(desc, 42);

	desc += "\n\nRequires melee weapon (except staff).";

	return desc;
}

void Ab_PowerStrike::execute(std::vector<ActorPtr>& targets, sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea) {
	Combat::WeaponAttack(user, targets[0], 2.0, false, abilityOptions);
	Combat::WeaponAttack(user, targets[0], offHandBasicMultiplier, true, abilityOptions);
}