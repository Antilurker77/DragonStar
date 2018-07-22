// ==================================
//
// ab_dragonfireBolt.cpp
//
// ==================================

#include "../header/ab_dragonfireBolt.h"

#include "../../id/abilityID.h"
#include "../../id/abilityType.h"
#include "../../id/attribute.h"
#include "../../id/category.h"
#include "../../id/element.h"
#include "../../../hex/hexMath.h"

Ab_DragonfireBolt::Ab_DragonfireBolt() {
	setHarmfulSpellDefault();

	name = "Dragonfire Bolt";
	abilityID = AbilityID::DragonfireBolt;
	icon = "dragonfire_bolt.png";

	abilityTypes = {
		AbilityType::FireSpell
	};
	tier = 1;

	categories = {
		Category::Damaging,
		Category::SingleTarget,
		Category::Direct,
		Category::Spell
	};

	elements = { Element::Fire };

	castTime = 200;
	range = 4;
	aiSearchRange = range;
	mpCost = 25;
	cooldown = 1200;

	requireTargetsInArea = true;
	isGroundTargeted = false;

	usage = UseType::Cast;
}

std::vector<sf::Vector3i> Ab_DragonfireBolt::GetTargetArea(sf::Vector3i selectedTile) {
	std::vector<sf::Vector3i> area = { selectedTile };
	return area;
}

std::string Ab_DragonfireBolt::GetDescription() {
	std::string damage = "105";

	if (user != nullptr) {
		damage = std::to_string(Combat::ScalingAttackEstimate(user, 105.0, Attribute::INT, abilityOptions));
	}

	std::string desc = "Shoot a bolt of draconic flames at the target, dealing #damage " + damage + " #default fire damage.";
	desc = WordWrap::WrapString(desc, charPerLine);

	return desc;
}

void Ab_DragonfireBolt::execute(std::vector<ActorPtr>& targets, sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea) {
	Combat::ScalingAttack(user, targets[0], 105.0, Attribute::INT, abilityOptions);
}