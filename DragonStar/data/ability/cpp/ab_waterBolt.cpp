// ==================================
//
// ab_waterBolt.cpp
//
// ==================================

#include "../header/ab_waterBolt.h"

#include "../../id/abilityID.h"
#include "../../id/abilityType.h"
#include "../../id/attribute.h"
#include "../../id/auraID.h"
#include "../../id/category.h"
#include "../../id/element.h"

Ab_WaterBolt::Ab_WaterBolt() {
	setHarmfulSpellDefault();

	name = "Water Bolt";
	abilityID = AbilityID::WaterBolt;
	icon = "water_bolt.png";

	abilityTypes = {
		AbilityType::WaterSpell
	};
	tier = 1;

	categories = {
		Category::Damaging,
		Category::SingleTarget,
		Category::Direct,
		Category::Spell
	};

	elements = { Element::Water };

	castTime = 200;
	range = 4;
	aiSearchRange = range;
	mpCost = 5;

	requireTargetsInArea = true;
	isGroundTargeted = false;

	usage = UseType::Cast;
}

std::vector<sf::Vector3i> Ab_WaterBolt::GetTargetArea(sf::Vector3i selectedTile) {
	std::vector<sf::Vector3i> area = { selectedTile };
	return area;
}

std::string Ab_WaterBolt::GetDescription() {
	std::string damage = "40";

	if (user != nullptr) {
		damage = std::to_string(Combat::ScalingAttackEstimate(user, 40.0, Attribute::INT, abilityOptions));
	}

	std::string desc = "Shoot a bolt of water at the target, dealing #damage " + damage + " #default water damage.";
	desc = WordWrap::WrapString(desc, 42);

	return desc;
}

void Ab_WaterBolt::execute(std::vector<ActorPtr>& targets, sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea) {
	Combat::ScalingAttack(user, targets[0], 40.0, Attribute::INT, abilityOptions);
}