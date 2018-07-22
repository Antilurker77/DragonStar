// ==================================
//
// magicMissile.cpp
//
// ==================================

#include "../header/ab_magicMissile.h"

#include "../../id/abilityID.h"
#include "../../id/abilityType.h"
#include "../../id/attribute.h"
#include "../../id/auraID.h"
#include "../../id/category.h"
#include "../../id/element.h"
#include "../../../hex/hexMath.h"

Ab_MagicMissile::Ab_MagicMissile() {
	setHarmfulSpellDefault();

	name = "Magic Missile";
	abilityID = AbilityID::MagicMissile;
	icon = "magic_missile.png";

	abilityTypes = {
		AbilityType::ArcaneSpell
	};
	tier = 1;

	categories = {
		Category::Damaging,
		Category::SingleTarget,
		Category::Direct,
		Category::Spell
	};

	elements = { Element::Arcane };

	castTime = 200;
	range = 4;
	aiSearchRange = range;
	mpCost = 10;

	requireTargetsInArea = true;
	isGroundTargeted = false;

	usage = UseType::Cast;
}

std::vector<sf::Vector3i> Ab_MagicMissile::GetTargetArea(sf::Vector3i selectedTile) {
	std::vector<sf::Vector3i> area = { selectedTile };
	return area;
}

std::string Ab_MagicMissile::GetDescription() {
	std::string damage = "50";

	if (user != nullptr) {
		damage = std::to_string(Combat::ScalingAttackEstimate(user, 50.0, Attribute::INT, abilityOptions));
	}

	std::string desc = "Shoot a missile of arcane energy at the target, dealing #damage " + damage + " #default arcane damage.";
	desc = WordWrap::WrapString(desc, charPerLine);

	return desc;
}

void Ab_MagicMissile::execute(std::vector<ActorPtr>& targets, sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea) {
	Combat::ScalingAttack(user, targets[0], 50.0, Attribute::INT, abilityOptions);
}