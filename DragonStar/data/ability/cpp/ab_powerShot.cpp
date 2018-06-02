// ==================================
//
// ab_powerShot.cpp
//
// ==================================

#include "../header/ab_powerShot.h"

#include "../../id/abilityID.h"
#include "../../id/abilityType.h"
#include "../../id/attribute.h"
#include "../../id/auraID.h"
#include "../../id/category.h"
#include "../../id/element.h"
#include "../../id/equipType.h"

Ab_PowerShot::Ab_PowerShot() {
	setAttackDefault();

	name = "Power Shot";
	abilityID = AbilityID::PowerShot;
	icon = "power_shot.png";

	abilityTypes = {
		AbilityType::BowSkill
	};
	tier = 1;

	categories = {
		Category::Attack,
		Category::Damaging,
		Category::SingleTarget,
		Category::Direct
	};

	usableWeapons = {
		EquipType::Bow
	};

	spCost = 15;
	cooldown = 800;

	usage = UseType::Instant;

	requireTargetsInArea = true;
}

std::vector<sf::Vector3i> Ab_PowerShot::GetTargetArea(sf::Vector3i selectedTile) {
	std::vector<sf::Vector3i> tiles = { selectedTile };
	return tiles;
}

std::string Ab_PowerShot::GetDescription() {
	std::string damage = "180%";

	if (user != nullptr) {
		damage = std::to_string(Combat::WeaponAttackEstimate(user, 1.8, false, abilityOptions));
	}

	std::string desc = "Fire a powerful shot against the target, dealing #damage " + damage + " #default weapon damage.";
	desc = WordWrap::WrapString(desc, 42);

	desc += "\n\nRequires bow.";

	return desc;
}

void Ab_PowerShot::execute(std::vector<ActorPtr>& targets, sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea) {
	Combat::WeaponAttack(user, targets[0], 1.8, false, abilityOptions);
}