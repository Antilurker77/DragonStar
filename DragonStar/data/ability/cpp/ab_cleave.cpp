// ==================================
//
// ab_cleave.cpp
//
// ==================================

#include "../header/ab_cleave.h"

#include "../../id/abilityID.h"
#include "../../id/abilityType.h"
#include "../../id/attribute.h"
#include "../../id/category.h"
#include "../../id/element.h"
#include "../../id/equipType.h"
#include "../../../hex/hexMath.h"

Ab_Cleave::Ab_Cleave() {
	setAttackDefault();

	name = "Cleave";
	abilityID = AbilityID::Cleave;
	icon = "cleave.png";

	abilityTypes = {
		AbilityType::SwordSkill,
		AbilityType::AxeSkill,
		AbilityType::MaceSkill
	};

	tier = 1;

	categories = {
		Category::Attack,
		Category::Skill,
		Category::Damaging,
		Category::AreaOfEffect,
		Category::Direct
	};

	elements = {
		
	};

	usableWeapons = {
		EquipType::Sword1H,
		EquipType::Sword2H,
		EquipType::Axe1H,
		EquipType::Axe2H,
		EquipType::Mace1H,
		EquipType::Mace2H
	};

	castTime = 100;
	range = 1;
	aiSearchRange = 1;
	targetOutsideCursor = true;
	spCost = 20;
	cooldown = 750;

	requireTargetsInArea = true;
	keyTileRange = true;
	keyTile = sf::Vector3i(0, 1, -1);
	canDoubleStrike = false;

	ignoreBodyBlock = true;
	ignoreLineOfSight = true;
	areaIgnoreBodyBlock = true;
	areaIgnoreLineOfSight = false;
}

std::vector<sf::Vector3i> Ab_Cleave::GetTargetArea(sf::Vector3i selectedTile) {
	std::vector<sf::Vector3i> tiles = {
		sf::Vector3i(-1, 1, 0),
		sf::Vector3i(0, 1, -1),
		sf::Vector3i(1, 0, -1)
	};

	rotateArea(selectedTile, tiles);

	return tiles;
}

std::string Ab_Cleave::GetDescription() {
	std::string damage = "90%";

	if (user != nullptr) {
		damage = std::to_string(Combat::WeaponAttackEstimate(user, 0.9, false, abilityOptions));
	}

	std::string desc = "Strike in an arc in front of you, dealing #damage " + damage + " #default weapon damage to all enemies hit.";
	desc = WordWrap::WrapString(desc, charPerLine);

	desc += "\n\nRequires sword, axe, or mace.";

	return desc;
}

void Ab_Cleave::execute(std::vector<ActorPtr>& targets, sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea) {
	for (size_t i = 0; i < targets.size(); i++) {
		Combat::WeaponAttack(user, targets[i], 0.9, false, abilityOptions);
	}
}