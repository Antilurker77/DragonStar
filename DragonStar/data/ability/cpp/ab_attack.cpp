// ==================================
//
// ab_attack.cpp
//
// ==================================

#include "../header/ab_attack.h"

#include "../../id/abilityID.h"
#include "../../id/abilityType.h"
#include "../../id/category.h"
#include "../../id/element.h"
#include "../../../entity/actor.h"

Ab_Attack::Ab_Attack() {
	setAttackDefault();

	name = "Attack";
	abilityID = AbilityID::Attack;
	icon = "attack.png";

	abilityTypes = {
		AbilityType::AxeSkill,
		AbilityType::BowSkill,
		AbilityType::ClawSkill,
		AbilityType::DaggerSkill,
		AbilityType::MaceSkill,
		AbilityType::SpearSkill,
		AbilityType::StaffSkill,
		AbilityType::SwordSkill,
		AbilityType::WandSkill
	};
	tier = 1;

	categories = { 
		Category::Attack,
		Category::Damaging,
		Category::SingleTarget,
		Category::Direct
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
			desc += " with both weapons, dealing #damage " + damage + " #default weapon damage with your main hand and #damage " + damageOffHand + " #default weapon damage with your off-hand.";
			return desc;
		}
	}
	
	desc += ", dealing #damage " + damage + " #default weapon damage.";
	desc = WordWrap::WrapString(desc, 42);

	return desc;
}

void Ab_Attack::execute(std::vector<ActorPtr>& targets, sf::Vector3i cursor,std::vector<sf::Vector3i> targetArea) {
	Combat::WeaponAttack(user, targets[0], 1.0, false, abilityOptions);
	Combat::WeaponAttack(user, targets[0], offHandBasicMultiplier, true, abilityOptions);
}