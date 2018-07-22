// ==================================
//
// ab_frost.cpp
//
// ==================================

#include "../header/ab_frost.h"

#include "../../id/abilityID.h"
#include "../../id/abilityType.h"
#include "../../id/attribute.h"
#include "../../id/auraID.h"
#include "../../id/category.h"
#include "../../id/element.h"

Ab_Frost::Ab_Frost() {
	setHarmfulSpellDefault();

	name = "Frost";
	abilityID = AbilityID::Frost;
	icon = "frost.png";

	abilityTypes = {
		AbilityType::IceSpell
	};
	tier = 1;

	categories = {
		Category::Damaging,
		Category::SingleTarget,
		Category::Direct,
		Category::Spell
	};

	elements = { Element::Ice };

	castTime = 100;
	cooldown = 2000;
	range = 4;
	aiSearchRange = range;
	mpCost = 18;

	requireTargetsInArea = true;
	isGroundTargeted = false;
	ignoreLineOfSight = true;

	usage = UseType::Instant;
}

std::vector<sf::Vector3i> Ab_Frost::GetTargetArea(sf::Vector3i selectedTile) {
	std::vector<sf::Vector3i> area = { selectedTile };
	return area;
}

std::string Ab_Frost::GetDescription() {
	std::string damage = "25";

	if (user != nullptr) {
		damage = std::to_string(Combat::ScalingAttackEstimate(user, 25.0, Attribute::INT, abilityOptions));
	}

	std::string desc = "Envelope the target in chilling frost, dealing #damage " + damage + " #default ice damage and reducing the target's movement speed by 50% for 8s.";
	desc = WordWrap::WrapString(desc, charPerLine);

	return desc;
}

void Ab_Frost::execute(std::vector<ActorPtr>& targets, sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea) {
	auto result = Combat::ScalingAttack(user, targets[0], 25.0, Attribute::INT, abilityOptions);
	if (result.DidHit) {
		Combat::AddAuraStack(user, targets[0], AuraID::Frost);
	}
}