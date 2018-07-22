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
	abilityID = AbilityID::FlameSlash;
	icon = "flame_slash.png";

	abilityTypes = {
		AbilityType::SwordSkill
	};
	tier = 1;

	categories = {
		Category::Attack,
		Category::Skill,
		Category::Damaging,
		Category::SingleTarget,
		Category::Direct,
	};

	elements = {
		Element::Fire
	};

	usableWeapons = {
		EquipType::Sword1H,
		EquipType::Sword2H
	};

	mpCost = 10;
	spCost = 20;
	cooldown = 600;

	usage = UseType::Instant;

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

	std::string desc = "Coat your sword in flames and slash the target, dealing #damage " + damage + " #default fire damage and increasing the damage of your next fire ability by 10%. Lasts 8s.";
	desc = WordWrap::WrapString(desc, charPerLine);

	desc += "\n\nRequires sword.";

	return desc;
}

void Ab_FlameSlash::execute(std::vector<ActorPtr>& targets, sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea) {
	Combat::WeaponAttack(user, targets[0], 1.7, false, abilityOptions);
	Combat::WeaponAttack(user, targets[0], offHandBasicMultiplier, true, abilityOptions);
	Combat::AddAuraStack(user, user, AuraID::FlameSlash);
}