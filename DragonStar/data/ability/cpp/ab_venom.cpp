// ==================================
//
// venom.cpp
//
// ==================================

#include "../header/ab_venom.h"

#include "../../id/abilityID.h"
#include "../../id/abilityType.h"
#include "../../id/attribute.h"
#include "../../id/auraID.h"
#include "../../id/category.h"
#include "../../id/element.h"

Ab_Venom::Ab_Venom() {
	setHarmfulSpellDefault();

	name = "Venom";
	abilityID = AbilityID::Venom;
	icon = "venom.png";

	abilityTypes = {
		AbilityType::PoisonSpell
	};
	tier = 1;

	categories = {
		Category::Damaging,
		Category::SingleTarget,
		Category::Direct,
		Category::Spell
	};

	elements = { Element::Poison };

	castTime = 200;
	range = 4;
	aiSearchRange = range;
	mpCost = 15;

	requireTargetsInArea = true;
	isGroundTargeted = false;

	usage = UseType::Cast;
}

std::vector<sf::Vector3i> Ab_Venom::GetTargetArea(sf::Vector3i selectedTile) {
	std::vector<sf::Vector3i> area = { selectedTile };
	return area;
}

std::string Ab_Venom::GetDescription() {
	std::string mainDamage = "15";
	std::string dotDamage = "5";

	if (user != nullptr) {
		mainDamage = std::to_string(Combat::ScalingAttackEstimate(user, 15.0, Attribute::INT, abilityOptions));
		dotDamage = std::to_string(Combat::ScalingAttackEstimate(user, 5.0, Attribute::INT, abilityOptions));
	}

	std::string desc = "Lob a ball of venom at the target, dealing #damage " + mainDamage +
		" #default poison damage and an additional #damage " + dotDamage + " #default poison damage every 1s for 16s.";
	desc = WordWrap::WrapString(desc, charPerLine);

	return desc;
}

void Ab_Venom::execute(std::vector<ActorPtr>& targets, sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea) {
	auto result = Combat::ScalingAttack(user, targets[0], 15.0, Attribute::INT, abilityOptions);
	if (result.DidHit) {
		Combat::AddAuraStack(user, targets[0], AuraID::Venom);
	}
}