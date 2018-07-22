// ==================================
//
// shock.cpp
//
// ==================================

#include "../header/ab_shock.h"

#include "../../id/abilityID.h"
#include "../../id/abilityType.h"
#include "../../id/attribute.h"
#include "../../id/auraID.h"
#include "../../id/category.h"
#include "../../id/element.h"

Ab_Shock::Ab_Shock() {
	setHarmfulSpellDefault();

	name = "Shock";
	abilityID = AbilityID::Shock;
	icon = "shock.png";

	abilityTypes = {
		AbilityType::LightningSpell
	};
	tier = 1;

	categories = {
		Category::Damaging,
		Category::SingleTarget,
		Category::Direct,
		Category::Spell
	};

	elements = { Element::Lightning };

	castTime = 150;
	range = 4;
	aiSearchRange = range;
	mpCost = 8;

	requireTargetsInArea = true;
	isGroundTargeted = false;

	usage = UseType::Cast;
}

std::vector<sf::Vector3i> Ab_Shock::GetTargetArea(sf::Vector3i selectedTile) {
	std::vector<sf::Vector3i> area = { selectedTile };
	return area;
}

std::string Ab_Shock::GetDescription() {
	std::string damage = "38";

	if (user != nullptr) {
		damage = std::to_string(Combat::ScalingAttackEstimate(user, 38.0, Attribute::INT, abilityOptions));
	}

	std::string desc = "Electrocute the target, dealing #damage " + damage + " #default lightning damage.";
	desc = WordWrap::WrapString(desc, charPerLine);

	return desc;
}

void Ab_Shock::execute(std::vector<ActorPtr>& targets, sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea) {
	Combat::ScalingAttack(user, targets[0], 38.0, Attribute::INT, abilityOptions);
}