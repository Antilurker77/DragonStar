// ==================================
//
// ab_dragonBreath.cpp
//
// ==================================

#include "../header/ab_dragonBreath.h"

Ab_DragonBreath::Ab_DragonBreath() {
	setAttackDefault();

	name = "Dragon Breath";
	abilityID = AbilityID::RACIAL_DRAGON_BREATH;
	icon = "dragon_breath.png";

	abilityTypes = {
		AbilityType::TECH
	};
	tier = 1;

	categories = {
		Category::ATTACK,
		Category::DAMAGING,
		Category::AREA_OF_EFFECT,
		Category::DIRECT
	};

	elements = {
		Element::FIRE
	};

	castTime = 100;
	range = 1;
	aiSearchRange = 2;
	targetOutsideCursor = true;
	spCost = 25;
	cooldown = 2000;

	isAttack = false;
	requireTargetsInArea = true;
	keyTileRange = true;
	keyTile = sf::Vector3i(1, 1, -2);
	canDoubleStrike = false;

	ignoreBodyBlock = true;
	ignoreLineOfSight = true;
	areaIgnoreBodyBlock = true;
	areaIgnoreLineOfSight = false;
}

std::vector<sf::Vector3i> Ab_DragonBreath::GetTargetArea(sf::Vector3i selectedTile) {
	std::vector<sf::Vector3i> tiles = {
		sf::Vector3i(0, 1, -1),
		sf::Vector3i(0, 2, -2),
		sf::Vector3i(1, 1, -2),
		sf::Vector3i(1, 0, -1),
		sf::Vector3i(2, 0, -2),
	};

	rotateArea(selectedTile, tiles);

	return tiles;
}

std::string Ab_DragonBreath::GetDescription() {
	std::string damage = "30";

	if (user != nullptr) {
		damage = std::to_string(Combat::ScalingAttackEstimate(user, 30, Attribute::NONE, abilityOptions));
	}

	std::string desc = "Breathe fire, dealing #damage " + damage + " #default fire damage to all enemies\nin a cone of length 2 in front of you.";

	return desc;
}

void Ab_DragonBreath::execute(std::vector<ActorPtr>& targets, sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea) {
	for (size_t i = 0; i < targets.size(); i++) {
		Combat::ScalingAttack(user, targets[i], 30, Attribute::NONE, abilityOptions);
	}
}