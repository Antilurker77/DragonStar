// ==================================
//
// darkBolt.cpp
//
// ==================================

#include "../header/ab_darkBolt.h"

#include "../../id/abilityID.h"
#include "../../id/abilityType.h"
#include "../../id/attribute.h"
#include "../../id/category.h"
#include "../../id/element.h"
#include "../../../scene/battleScene.h"

Ab_DarkBolt::Ab_DarkBolt() {
	setHarmfulSpellDefault();

	name = "Dark Bolt";
	abilityID = AbilityID::DarkBolt;
	icon = "dark_bolt.png";

	abilityTypes = {
		AbilityType::DarkSpell
	};
	tier = 1;

	categories = {
		Category::Damaging,
		Category::SingleTarget,
		Category::Direct,
		Category::Spell
	};

	elements = { Element::Dark };

	castTime = 250;
	range = 4;
	aiSearchRange = range;
	mpCost = 25;

	requireTargetsInArea = true;
	isGroundTargeted = false;

	usage = UseType::Cast;
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

	std::string desc = "Shoot a bolt of darkness at the target, dealing #damage " + damage + " #default dark damage.";
	desc = WordWrap::WrapString(desc, charPerLine);

	return desc;
}

void Ab_DarkBolt::execute(std::vector<ActorPtr>& targets, sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea) {
	Combat::ScalingAttack(user, targets[0], 65.0, Attribute::INT, abilityOptions);
}