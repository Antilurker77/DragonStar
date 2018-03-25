// ==================================
//
// ab_boulder.cpp
//
// ==================================

#include "../header/ab_boulder.h"

#include "../../id/abilityID.h"
#include "../../id/abilityType.h"
#include "../../id/attribute.h"
#include "../../id/category.h"
#include "../../id/element.h"
#include "../../../hex/hexMath.h"

Ab_Boulder::Ab_Boulder() {
	setHarmfulSpellDefault();

	name = "Boulder";
	abilityID = AbilityID::BOULDER;
	icon = "boulder.png";

	abilityTypes = {
		AbilityType::EARTH_SPELL
	};
	tier = 1;

	categories = {
		Category::DAMAGING,
		Category::SINGLE_TARGET,
		Category::DIRECT,
		Category::SPELL
	};

	elements = { Element::EARTH };

	castTime = 250;
	range = 4;
	aiSearchRange = range;
	mpCost = 2;
	spCost = 20;

	requireTargetsInArea = true;
	isGroundTargeted = false;

	usage = UseType::CAST;
}

std::vector<sf::Vector3i> Ab_Boulder::GetTargetArea(sf::Vector3i selectedTile) {
	std::vector<sf::Vector3i> area = { selectedTile };
	return area;
}

std::string Ab_Boulder::GetDescription() {
	std::string damage = "62";

	if (user != nullptr) {
		damage = std::to_string(Combat::ScalingAttackEstimate(user, 62.0, Attribute::INT, abilityOptions));
	}

	std::string desc = "Conjure a huge boulder and throw it at the target, dealing #damage " + damage + " #default earth damage.";
	desc = WordWrap::WrapString(desc, 42);

	return desc;
}

void Ab_Boulder::execute(std::vector<ActorPtr>& targets, sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea) {
	Combat::ScalingAttack(user, targets[0], 62.0, Attribute::INT, abilityOptions);
}