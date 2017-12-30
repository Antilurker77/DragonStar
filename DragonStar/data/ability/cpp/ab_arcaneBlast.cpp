// ==================================
//
// ab_arcaneBlast.cpp
//
// ==================================

#include "../header/ab_arcaneBlast.h"
#include "../../../hex/hexMath.h"

Ab_ArcaneBlast::Ab_ArcaneBlast() {
	setHarmfulSpellDefault();

	name = "Arcane Blast";
	abilityID = AbilityID::ARCANE_BLAST;
	icon = "arcane_blast.png";

	tier = 1;
	abilityTypes = {
		AbilityType::ARCANE_SPELL
	};

	categories = {
		Category::DAMAGING,
		Category::SINGLE_TARGET,
		Category::DIRECT,
		Category::SPELL
	};

	elements = { Element::ARCANE };

	castTime = 100;
	cooldown = 1000;
	range = 4;
	aiSearchRange = range;
	mpCost = 20;

	requireTargetsInArea = true;
	isGroundTargeted = false;

	usage = UseType::INSTANT;
}

std::vector<sf::Vector3i> Ab_ArcaneBlast::GetTargetArea(sf::Vector3i selectedTile) {
	std::vector<sf::Vector3i> area = { selectedTile };
	return area;
}

std::string Ab_ArcaneBlast::GetDescription() {
	std::string damage = "90";

	if (user != nullptr) {
		damage = std::to_string(Combat::ScalingAttackEstimate(user, 90.0, Attribute::INT, abilityOptions));
	}

	std::string desc = "Blast the target with arcane energy, dealing\n#damage " + damage + " #default arcane damage.";
	return desc;
}

void Ab_ArcaneBlast::execute(std::vector<ActorPtr>& targets, sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea) {
	Combat::ScalingAttack(user, targets[0], 90.0, Attribute::INT, abilityOptions);
}