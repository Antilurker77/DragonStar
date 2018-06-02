// ==================================
//
// ab_healingRain.cpp
//
// ==================================

#include "../header/ab_healingRain.h"

#include "../../id/abilityID.h"
#include "../../id/abilityType.h"
#include "../../id/attribute.h"
#include "../../id/auraID.h"
#include "../../id/category.h"
#include "../../id/element.h"
#include "../../../hex/hexMath.h"
#include "../../../scene/battleScene.h"
#include "../../../hex/hexMath.h"

Ab_HealingRain::Ab_HealingRain() {
	setHelpfulSpellDefault();

	name = "Healing Rain";
	abilityID = AbilityID::HealingRain;
	icon = "healing_rain.png";

	abilityTypes = {
		AbilityType::NatureHeal
	};
	tier = 3;

	categories = {
		Category::Healing,
		Category::AreaOfEffect,
		Category::OverTime,
		Category::Spell
	};

	elements = { Element::NatureHeal };

	castTime = 225;
	range = 2;
	aiSearchRange = range;
	mpCost = 60;
	cooldown = 4000;

	requireTargetsInArea = false;
	isGroundTargeted = true;

	areaIgnoreBodyBlock = true;

	usage = UseType::Cast;
}

std::vector<sf::Vector3i> Ab_HealingRain::GetTargetArea(sf::Vector3i selectedTile) {
	std::vector<sf::Vector3i> area = Hex::FilledHexagon(selectedTile, 2);
	if (battleScene != nullptr) {
		area = battleScene->GetLineOfSight(selectedTile, area, user->IsPlayer(), true, false);
	}
	return area;
}

std::string Ab_HealingRain::GetDescription() {
	std::string heal = "8";

	if (user != nullptr) {
		heal = std::to_string(Combat::ScalingHealEstimate(user, 8.0, Attribute::HP, abilityOptions));
	}

	std::string desc = "Call rain on a targeted area of radius 2, healing #heal " + heal + " #default HP every 1s for 20s.";
	desc = WordWrap::WrapString(desc, 42);

	return desc;
}

void Ab_HealingRain::execute(std::vector<ActorPtr>& targets, sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea) {
	for (auto tile : targetArea) {
		Combat::CreateGroundEffect(user, battleScene, AuraID::HealingRain, tile);
	}
}