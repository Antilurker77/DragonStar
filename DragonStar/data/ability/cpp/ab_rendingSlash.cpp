// ==================================
//
// ab_rendingSlash.cpp
//
// ==================================

#include "../header/ab_rendingSlash.h"

#include "../../id/abilityID.h"
#include "../../id/abilityType.h"
#include "../../id/attribute.h"
#include "../../id/auraID.h"
#include "../../id/category.h"
#include "../../id/element.h"
#include "../../id/equipType.h"

Ab_RendingSlash::Ab_RendingSlash() {
	setAttackDefault();

	name = "Rending Slash";
	abilityID = AbilityID::RendingSlash;
	icon = "rending_slash.png";

	abilityTypes = {
		AbilityType::AxeSkill,
		AbilityType::ClawSkill,
		AbilityType::DaggerSkill,
		AbilityType::SwordSkill
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
		EquipType::Sword1H,
		EquipType::Sword2H,
		EquipType::Axe1H,
		EquipType::Axe2H,
		EquipType::Dagger,
		EquipType::Claw
	};

	spCost = 25;
	cooldown = 2000;

	usage = UseType::Instant;

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

	std::string desc = "Slash the target, dealing #damage " + damage + " #default weapon damage plus #damage " + dotDamage + " #default physical damage every 1s for 10s.";
	desc = WordWrap::WrapString(desc, 42);

	desc += "\n\nRequires sword, axe, or dagger.";

	return desc;
}

void Ab_RendingSlash::execute(std::vector<ActorPtr>& targets, sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea) {
	auto result = Combat::WeaponAttack(user, targets[0], 1.1, false, abilityOptions);
	if (result.DidHit) {
		Combat::AddAuraStack(user, targets[0], AuraID::RendingSlash);
	}
	Combat::WeaponAttack(user, targets[0], offHandBasicMultiplier, true, abilityOptions);
}