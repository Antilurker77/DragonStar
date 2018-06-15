// ==================================
//
// ab_dualStrike.cpp
//
// ==================================

#include "../header/ab_dualStrike.h"

#include "../../id/abilityID.h"
#include "../../id/abilityType.h"
#include "../../id/attribute.h"
#include "../../id/auraID.h"
#include "../../id/category.h"
#include "../../id/element.h"
#include "../../id/equipType.h"
#include "../../../entity/actor.h"

Ab_DualStrike::Ab_DualStrike() {
	setAttackDefault();

	name = "Dual Strike";
	abilityID = AbilityID::DualStrike;
	icon = "dual_strike.png";

	abilityTypes = {
		AbilityType::AxeSkill,
		AbilityType::ClawSkill,
		AbilityType::DaggerSkill,
		AbilityType::MaceSkill,
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
		EquipType::Axe1H,
		EquipType::Mace1H,
		EquipType::Dagger,
		EquipType::Claw
	};

	spCost = 25;
	cooldown = 1200;

	usage = UseType::Instant;

	requireTargetsInArea = true;
}

std::vector<sf::Vector3i> Ab_DualStrike::GetTargetArea(sf::Vector3i selectedTile) {
	std::vector<sf::Vector3i> tiles = { selectedTile };
	return tiles;
}

std::string Ab_DualStrike::GetDescription() {
	std::string damageMainHand = "160%";
	std::string damageOffHand = "160%";
	std::string damageTotal = ".";

	if (user != nullptr) {
		int mh = Combat::WeaponAttackEstimate(user, 1.6, false, abilityOptions);
		int oh = Combat::WeaponAttackEstimate(user, 1.6, true, abilityOptions);
		
		damageMainHand = std::to_string(mh);
		damageOffHand = std::to_string(oh);
		damageTotal = " (#damage " + std::to_string(mh + oh) + " #default total).";
	}

	std::string desc = "Strike the target fiercly with both weapons, dealing #damage " + damageMainHand + " #default weapon damage with your main hand and";
	desc += " #damage " + damageOffHand + " #default weapon damage with your off-hand" + damageTotal;
	desc = WordWrap::WrapString(desc, 42);

	desc += "\n\nRequires dual wielding weapons.";

	return desc;
}

void Ab_DualStrike::execute(std::vector<ActorPtr>& targets, sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea) {
	Combat::WeaponAttack(user, targets[0], 1.6, false, abilityOptions);
	Combat::WeaponAttack(user, targets[0], 1.6, true, abilityOptions);
}

bool Ab_DualStrike::customUseCondition() {
	if (user != nullptr) {
		return user->IsDualWielding();
	}
	return false;
}