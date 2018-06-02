// ==================================
//
// psionicMissile.cpp
//
// ==================================

#include "../header/ab_psionicMissile.h"

#include "../../id/abilityID.h"
#include "../../id/abilityType.h"
#include "../../id/attribute.h"
#include "../../id/auraID.h"
#include "../../id/category.h"
#include "../../id/element.h"
#include "../../../hex/hexMath.h"

Ab_PsionicMissile::Ab_PsionicMissile() {
	setHarmfulSpellDefault();

	name = "Psionic Missile";
	abilityID = AbilityID::PsionicMissile;
	icon = "psionic_missile.png";

	abilityTypes = {
		AbilityType::MindSpell
	};
	tier = 1;

	categories = {
		Category::Damaging,
		Category::SingleTarget,
		Category::Direct,
		Category::Spell
	};

	elements = { Element::Mind };

	castTime = 250;
	range = 4;
	aiSearchRange = range;
	mpCost = 12;

	requireTargetsInArea = true;
	isGroundTargeted = false;

	usage = UseType::Cast;
}

std::vector<sf::Vector3i> Ab_PsionicMissile::GetTargetArea(sf::Vector3i selectedTile) {
	std::vector<sf::Vector3i> area = { selectedTile };
	return area;
}

std::string Ab_PsionicMissile::GetDescription() {
	std::string damage = "60";

	if (user != nullptr) {
		damage = std::to_string(Combat::ScalingAttackEstimate(user, 60.0, Attribute::INT, abilityOptions));
	}

	std::string desc = "Create a missile of psionic energy and shoot it at the target, dealing #damage " + damage + " #default mind damage.";
	desc = WordWrap::WrapString(desc, 42);

	return desc;
}

void Ab_PsionicMissile::execute(std::vector<ActorPtr>& targets, sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea) {
	Combat::ScalingAttack(user, targets[0], 60.0, Attribute::INT, abilityOptions);
}