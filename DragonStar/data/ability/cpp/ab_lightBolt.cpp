// ==================================
//
// ab_lightBolt.cpp
//
// ==================================

#include "../header/ab_lightBolt.h"

#include "../../id/abilityID.h"
#include "../../id/abilityType.h"
#include "../../id/attribute.h"
#include "../../id/category.h"
#include "../../id/element.h"
#include "../../../scene/battleScene.h"

Ab_LightBolt::Ab_LightBolt() {
	setHarmfulSpellDefault();

	name = "Light Bolt";
	abilityID = AbilityID::LIGHT_BOLT;
	icon = "light_bolt.png";

	abilityTypes = {
		AbilityType::LIGHT_SPELL
	};
	tier = 1;

	categories = {
		Category::DAMAGING,
		Category::SINGLE_TARGET,
		Category::DIRECT,
		Category::SPELL
	};

	elements = { Element::LIGHT };

	castTime = 200;
	range = 4;
	aiSearchRange = range;
	mpCost = 15;

	bonusLifeLeech = 0.50;

	requireTargetsInArea = true;
	isGroundTargeted = false;

	usage = UseType::CAST;
}

std::vector<sf::Vector3i> Ab_LightBolt::GetTargetArea(sf::Vector3i selectedTile) {
	std::vector<sf::Vector3i> area = { selectedTile };
	return area;
}

std::string Ab_LightBolt::GetDescription() {
	std::string damage = "50";

	if (user != nullptr) {
		damage = std::to_string(Combat::ScalingAttackEstimate(user, 50.0, Attribute::INT, abilityOptions));
	}

	std::string desc = "Shoot a bolt of light at the target, dealing #damage " + damage + " #default light damage. Heals for 50% of the damage dealt.";
	desc = WordWrap::WrapString(desc, 42);

	return desc;
}

void Ab_LightBolt::execute(std::vector<ActorPtr>& targets, sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea) {
	Combat::ScalingAttack(user, targets[0], 50.0, Attribute::INT, abilityOptions);
}