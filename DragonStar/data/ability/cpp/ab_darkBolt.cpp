// ==================================
//
// darkBolt.cpp
//
// ==================================

#include "../header/ab_darkBolt.h"
#include "../../../hex/hexMath.h"

Ab_DarkBolt::Ab_DarkBolt() {
	setHarmfulSpellDefault();

	name = "Dark Bolt";
	abilityID = AbilityID::DARK_BOLT;
	icon = "dark_bolt.png";

	abilityTypes = {
		AbilityType::DARK_SPELL
	};
	tier = 1;

	categories = {
		Category::DAMAGING,
		Category::SINGLE_TARGET,
		Category::DIRECT,
		Category::SPELL
	};

	elements = { Element::DARK };

	castTime = 250;
	range = 4;
	aiSearchRange = range;
	mpCost = 25;

	requireTargetsInArea = true;
	isGroundTargeted = false;

	usage = UseType::CAST;
}

std::vector<sf::Vector3i> Ab_DarkBolt::GetTargetArea(sf::Vector3i selectedTile) {
	std::vector<sf::Vector3i> area = { selectedTile };
	return area;
}

std::string Ab_DarkBolt::GetDescription() {
	std::string damage = "65";

	if (user != nullptr) {
		damage = std::to_string(Combat::ScalingAttackEstimate(user, 65.0, Attribute::INT, abilityOptions));
	}

	std::string desc = "Shoot a bolt of darkness at the target, dealing\n#damage " + damage + " #default dark damage.";
	return desc;
}

void Ab_DarkBolt::execute(std::vector<ActorPtr>& targets, sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea) {
	Combat::ScalingAttack(user, targets[0], 65.0, Attribute::INT, abilityOptions);
}