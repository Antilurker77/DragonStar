// ==================================
//
// ab_splash.cpp
//
// ==================================

#include "../header/ab_splash.h"
#include "../../../scene/battleScene.h"
#include "../../../hex/hexMath.h"

Ab_Splash::Ab_Splash() {
	setHarmfulSpellDefault();

	name = "Splash";
	abilityID = AbilityID::SPLASH;
	icon = "splash.png";

	abilityTypes = {
		AbilityType::WATER_SPELL
	};
	tier = 1;

	categories = { 
		Category::DAMAGING,
		Category::AREA_OF_EFFECT,
		Category::DIRECT,
		Category::SPELL	
	};

	elements = { Element::WATER };

	castTime = 250;
	range = 4;
	aiSearchRange = range;
	mpCost = 15;
	cooldown = 900;

	requireTargetsInArea = true;
	isGroundTargeted = true;

	areaIgnoreBodyBlock = true;

	usage = UseType::CAST;
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

	std::string desc = "Splash water on to a targeted area of radius 1,\ndealing #damage " + damage + " #default water damage.";

	return desc;
}

void Ab_Splash::execute(std::vector<ActorPtr>& targets, sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea) {
	for (size_t i = 0; i < targets.size(); i++) {
		Combat::ScalingAttack(user, targets[i], 30.0, Attribute::INT, abilityOptions);
	}
}