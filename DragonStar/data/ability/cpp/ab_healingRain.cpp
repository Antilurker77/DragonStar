// ==================================
//
// ab_healingRain.cpp
//
// ==================================

#include "../header/ab_healingRain.h"
#include "../../../scene/battleScene.h"
#include "../../../hex/hexMath.h"

Ab_HealingRain::Ab_HealingRain() {
	setHelpfulSpellDefault();

	name = "Healing Rain";
	abilityID = AbilityID::HEALING_RAIN;
	icon = "healing_rain.png";

	abilityTypes = {
		AbilityType::NATURE_HEAL
	};
	tier = 3;

	categories = {
		Category::HEALING,
		Category::AREA_OF_EFFECT,
		Category::OVER_TIME,
		Category::SPELL
	};

	elements = { Element::NATURE_HEAL };

	castTime = 225;
	range = 2;
	aiSearchRange = range;
	mpCost = 60;
	cooldown = 4000;

	requireTargetsInArea = false;
	isGroundTargeted = true;

	areaIgnoreBodyBlock = true;

	usage = UseType::CAST;
}

std::vector<sf::Vector3i> Ab_HealingRain::GetTargetArea(sf::Vector3i selectedTile) {
	std::vector<sf::Vector3i> area = Hex::FilledHexagon(selectedTile, 2);
	if (battleScene != nullptr) {
		area = battleScene->GetLineOfSight(selectedTile, area, user->IsPlayer(), true, false);
	}
	return area;
}

std::string Ab_HealingRain::GetDescription() {
	std::string heal = "5";

	if (user != nullptr) {
		heal = std::to_string(Combat::ScalingHealEstimate(user, 5.0, Attribute::HP, abilityOptions));
	}

	std::string desc = "Call rain on a targeted area of radius 2, healing\n#heal " + heal + " #default HP every 1s for 20s.";

	return desc;
}

void Ab_HealingRain::execute(std::vector<ActorPtr>& targets, sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea) {
	for (auto tile : targetArea) {
		Combat::CreateGroundEffect(user, battleScene, AuraID::HEALING_RAIN, tile);
	}
}