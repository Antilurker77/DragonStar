// ==================================
//
// ab_splash.cpp
//
// ==================================

#include "../header/ab_splash.h"
#include "../../../scene/battleScene.h"
#include "../../../hex/hexMath.h"

#include "../../id/abilityID.h"
#include "../../id/abilityType.h"
#include "../../id/attribute.h"
#include "../../id/auraID.h"
#include "../../id/category.h"
#include "../../id/element.h"

Ab_Splash::Ab_Splash() {
	setHarmfulSpellDefault();

	name = "Splash";
	abilityID = AbilityID::Splash;
	icon = "splash.png";

	abilityTypes = {
		AbilityType::WaterSpell
	};
	tier = 1;

	categories = { 
		Category::Damaging,
		Category::AreaOfEffect,
		Category::Direct,
		Category::Spell	
	};

	elements = { Element::Water };

	castTime = 250;
	range = 4;
	aiSearchRange = range;
	mpCost = 15;
	cooldown = 900;

	requireTargetsInArea = true;
	isGroundTargeted = true;

	areaIgnoreBodyBlock = true;

	usage = UseType::Cast;
}

std::vector<sf::Vector3i> Ab_Splash::GetTargetArea(sf::Vector3i selectedTile) {
	std::vector<sf::Vector3i> area = Hex::FilledHexagon(selectedTile, 1);
	if (battleScene != nullptr) {
		area = battleScene->GetLineOfSight(selectedTile, area, user->IsPlayer(), true, false);
	}
	return area;
}

std::string Ab_Splash::GetDescription() {
	std::string damage = "30";

	if (user != nullptr) {
		damage = std::to_string(Combat::ScalingAttackEstimate(user, 30.0, Attribute::INT, abilityOptions));
	}

	std::string desc = "Splash water on to a targeted area of radius 1, dealing #damage " + damage + " #default water damage.";
	desc = WordWrap::WrapString(desc, 42);

	return desc;
}

void Ab_Splash::execute(std::vector<ActorPtr>& targets, sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea) {
	for (size_t i = 0; i < targets.size(); i++) {
		Combat::ScalingAttack(user, targets[i], 30.0, Attribute::INT, abilityOptions);
	}
}