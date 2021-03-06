// ==================================
//
// ab_fireball.cpp
//
// ==================================

#include "../header/ab_fireball.h"

#include "../../id/abilityID.h"
#include "../../id/abilityType.h"
#include "../../id/attribute.h"
#include "../../id/category.h"
#include "../../id/element.h"
#include "../../../hex/hexMath.h"
#include "../../../entity/actor.h"
#include "../../../hex/hexMath.h"
#include "../../../scene/battleScene.h"

Ab_Fireball::Ab_Fireball() {
	setHarmfulSpellDefault();

	name = "Fireball";
	abilityID = AbilityID::Fireball;
	icon = "fireball.png";

	abilityTypes = {
		AbilityType::FireSpell
	};
	tier = 2;

	categories = {
		Category::Damaging,
		Category::AreaOfEffect,
		Category::Direct,
		Category::Spell
	};

	elements = { Element::Fire };

	castTime = 200;
	range = 4;
	aiSearchRange = range;
	mpCost = 30;
	cooldown = 1600;

	requireTargetsInArea = false;
	isGroundTargeted = true;

	areaIgnoreBodyBlock = true;

	usage = UseType::Cast;
}

std::vector<sf::Vector3i> Ab_Fireball::GetTargetArea(sf::Vector3i selectedTile) {
	std::vector<sf::Vector3i> area = Hex::FilledHexagon(selectedTile, 1);
	if (battleScene != nullptr) {
		// stops opeque non-passible tiles from being included
		area = battleScene->GetLineOfSight(selectedTile, area, user->IsPlayer(), true, false);
	}
	return area;
}

std::string Ab_Fireball::GetDescription() {
	std::string damageCenter = "64";
	std::string damageOutside = "32";

	if (user != nullptr) {
		damageCenter = std::to_string(Combat::ScalingAttackEstimate(user, 64.0, Attribute::INT, abilityOptions));
		damageOutside = std::to_string(Combat::ScalingAttackEstimate(user, 32.0, Attribute::INT, abilityOptions));
	}

	std::string desc = "Hurl a massive ball of fire at the target location, dealing #damage " + damageCenter + " #default fire damage " +
		"to the enemy at the center and #damage " + damageOutside + " #default fire damage to the rest.";
	desc = WordWrap::WrapString(desc, charPerLine);

	return desc;
}

void Ab_Fireball::execute(std::vector<ActorPtr>& targets, sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea) {
	for (size_t i = 0; i < targets.size(); i++) {
		if (targets[i]->GetHexPosition() == cursor) {
			Combat::ScalingAttack(user, targets[i], 64.0, Attribute::INT, abilityOptions);
		}
		else {
			Combat::ScalingAttack(user, targets[i], 32.0, Attribute::INT, abilityOptions);
		}
	}
}