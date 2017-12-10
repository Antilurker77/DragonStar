// ==================================
//
// magicMissile.cpp
//
// ==================================

#include "../header/ab_magicMissile.h"
#include "../../../hex/hexMath.h"

Ab_MagicMissile::Ab_MagicMissile() {
	setHarmfulSpellDefault();

	name = "Magic Missile";
	abilityID = AbilityID::MAGIC_MISSILE;
	icon = "magic_missile.png";

	abilityTypes = {
		AbilityType::ARCANE_SPELL
	};
	tier = 1;

	categories = {
		Category::DAMAGING,
		Category::SINGLE_TARGET,
		Category::DIRECT,
		Category::SPELL
	};

	elements = { Element::ARCANE };

	castTime = 200;
	range = 4;
	aiSearchRange = range;
	mpCost = 15;

	requireTargetsInArea = true;
	isGroundTargeted = false;

	usage = UseType::CAST;
}

std::vector<sf::Vector3i> Ab_MagicMissile::GetTargetArea(sf::Vector3i selectedTile) {
	std::vector<sf::Vector3i> area = { selectedTile };
	return area;
}

std::string Ab_MagicMissile::GetDescription() {
	std::string damage = "20";

	if (user != nullptr) {
		damage = std::to_string(Combat::ScalingAttackEstimate(user, 20, Attribute::INT, abilityOptions));
	}

	std::string desc = "Shoot a missile of arcane energy at the target,\ndealing #damage " + damage + " #default arcane damage.";
	return desc;
}

void Ab_MagicMissile::execute(std::vector<ActorPtr>& targets, sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea) {
	Combat::ScalingAttack(user, targets[0], 20, Attribute::INT, abilityOptions);
}