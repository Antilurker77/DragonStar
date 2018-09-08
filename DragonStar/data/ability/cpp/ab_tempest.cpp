// ==================================
//
// ab_tempest.cpp
//
// ==================================

#include "../header/ab_tempest.h"

#include "../../id/abilityID.h"
#include "../../id/abilityType.h"
#include "../../id/attribute.h"
#include "../../id/auraID.h"
#include "../../id/category.h"
#include "../../id/element.h"
#include "../../id/equipType.h"
#include "../../../hex/hexMath.h"

Ab_Tempest::Ab_Tempest() {
	setAttackDefault();

	name = "Tempest";
	abilityID = AbilityID::Tempest;
	icon = "tempest.png";

	abilityTypes = {
		AbilityType::SpearSkill
	};

	tier = 2;

	categories = {
		Category::Attack,
		Category::Skill,
		Category::Damaging,
		Category::AreaOfEffect,
		Category::Direct
	};

	elements = {
		Element::Lightning,
		Element::Water,
		Element::Wind
	};

	usableWeapons = {
		EquipType::Spear
	};

	castTime = 100;
	range = 1;
	aiSearchRange = 2;
	targetOutsideCursor = true;
	mpCost = 50;
	spCost = 40;
	cooldown = 1600;

	requireTargetsInArea = true;
	keyTileRange = true;
	keyTile = sf::Vector3i(0, 1, -1);
	canDoubleStrike = false;

	ignoreBodyBlock = true;
	ignoreLineOfSight = true;
	areaIgnoreBodyBlock = true;
	areaIgnoreLineOfSight = false;
}

std::vector<sf::Vector3i> Ab_Tempest::GetTargetArea(sf::Vector3i selectedTile) {
	std::vector<sf::Vector3i> tiles = {
		sf::Vector3i(-1, 1, 0),
		sf::Vector3i(0, 1, -1),
		sf::Vector3i(1, 0, -1),
		sf::Vector3i(0, 2, -2),
		sf::Vector3i(-1, 2, -1),
		sf::Vector3i(1, 1, -2)
	};

	rotateArea(selectedTile, tiles);

	return tiles;
}

std::string Ab_Tempest::GetDescription() {
	std::string damage = "125%";

	if (user != nullptr) {
		damage = std::to_string(Combat::WeaponAttackEstimate(user, 1.25, false, abilityOptions));
	}

	std::string desc = "Channel a raging tempest and strike an area in front of you, dealing #damage " + damage + " #default lightning, water, and wind damage";
	desc += " and increasing the amount of lightning, water, and wind damage they take by 10% for 12s.";
	desc = WordWrap::WrapString(desc, charPerLine);

	desc += "\n\nRequires spear.";

	return desc;
}

void Ab_Tempest::execute(std::vector<ActorPtr>& targets, sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea) {
	for (size_t i = 0; i < targets.size(); i++) {
		auto result = Combat::WeaponAttack(user, targets[i], 1.25, false, abilityOptions);
		if (result.DidHit) {
			Combat::AddAuraStack(user, targets[i], AuraID::Tempest);
		}
	}
}