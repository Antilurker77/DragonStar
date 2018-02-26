// ==================================
//
// ab_flameSlash.cpp
//
// ==================================

#include "../header/ab_flameSlash.h"

#include "../../id/abilityID.h"
#include "../../id/abilityType.h"
#include "../../id/attribute.h"
#include "../../id/auraID.h"
#include "../../id/category.h"
#include "../../id/element.h"
#include "../../id/equipType.h"
#include "../../../hex/hexMath.h"

Ab_FlameSlash::Ab_FlameSlash() {
	setAttackDefault();

	name = "Flame Slash";
	abilityID = AbilityID::FLAME_SLASH;
	icon = "flame_slash.png";

	abilityTypes = {
		AbilityType::SWORD_SKILL
	};
	tier = 1;

	categories = {
		Category::ATTACK,
		Category::DAMAGING,
		Category::SINGLE_TARGET,
		Category::DIRECT,
	};

	elements = {
		Element::FIRE
	};

	usableWeapons = {
		EquipType::SWORD_1H,
		EquipType::SWORD_2H
	};

	mpCost = 10;
	spCost = 20;
	cooldown = 600;

	usage = UseType::INSTANT;

	requireTargetsInArea = true;
}

std::vector<sf::Vector3i> Ab_FlameSlash::GetTargetArea(sf::Vector3i selectedTile) {
	std::vector<sf::Vector3i> tiles = { selectedTile };
	return tiles;
}

std::string Ab_FlameSlash::GetDescription() {
	std::string damage = "170%";

	if (user != nullptr) {
		damage = std::to_string(Combat::WeaponAttackEstimate(user, 1.7, false, abilityOptions));
	}

	std::string desc = "Coat your sword in flames and slash the target,\ndealing #damage " + damage + " #default fire damage and increasing the damage\nof your next fire ability by 10%. Lasts 8s.";
	desc += "\n\nRequires sword.";

	return desc;
}

void Ab_FlameSlash::execute(std::vector<ActorPtr>& targets, sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea) {
	Combat::WeaponAttack(user, targets[0], 1.7, false, abilityOptions);
	Combat::WeaponAttack(user, targets[0], offHandBasicMultiplier, true, abilityOptions);
	Combat::AddAuraStack(user, user, AuraID::FLAME_SLASH);
}