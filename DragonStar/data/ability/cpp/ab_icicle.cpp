// ==================================
//
// ab_icicle.cpp
//
// ==================================

#include "../header/ab_icicle.h"

#include "../../id/abilityID.h"
#include "../../id/abilityType.h"
#include "../../id/attribute.h"
#include "../../id/auraID.h"
#include "../../id/category.h"
#include "../../id/element.h"

Ab_Icicle::Ab_Icicle() {
	setHarmfulSpellDefault();

	name = "Icicle";
	abilityID = AbilityID::Icicle;
	icon = "icicle.png";

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

	castTime = 200;
	range = 4;
	aiSearchRange = range;
	mpCost = 10;

	requireTargetsInArea = true;
	isGroundTargeted = false;

	usage = UseType::Cast;
}

std::vector<sf::Vector3i> Ab_Icicle::GetTargetArea(sf::Vector3i selectedTile) {
	std::vector<sf::Vector3i> area = { selectedTile };
	return area;
}

std::string Ab_Icicle::GetDescription() {
	std::string damage = "38";

	if (user != nullptr) {
		damage = std::to_string(Combat::ScalingAttackEstimate(user, 38.0, Attribute::INT, abilityOptions));
	}

	std::string desc = "Hurl an icicle at the target, dealing #damage " + damage + " #default ice damage and reducing the target's movement speed by 20% for 5s.";
	desc = WordWrap::WrapString(desc, charPerLine);

	return desc;
}

void Ab_Icicle::execute(std::vector<ActorPtr>& targets, sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea) {
	auto result = Combat::ScalingAttack(user, targets[0], 38.0, Attribute::INT, abilityOptions);
	if (result.DidHit) {
		Combat::AddAuraStack(user, targets[0], AuraID::Icicle);
	}
}