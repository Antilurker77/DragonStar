// ==================================
//
// ab_commandingShout.cpp
//
// ==================================

#include "../header/ab_commandingShout.h"

#include "../../id/abilityID.h"
#include "../../id/abilityType.h"
#include "../../id/auraID.h"
#include "../../id/category.h"
#include "../../id/element.h"
#include "../../../scene/battleScene.h"

Ab_CommandingShout::Ab_CommandingShout() {
	setHelpfulSpellDefault();

	name = "Commanding Shout";
	abilityID = AbilityID::RacialCommandingShout;
	icon = "commanding_shout.png";

	abilityTypes = {
		AbilityType::Tech
	};
	tier = 1;

	categories = {
		Category::AreaOfEffect
	};

	elements = {
		Element::Physical
	};

	castTime = 0;
	cooldown = 18000;
	range = 0;
	aiSearchRange = 0;

	usage = UseType::Instant;

	requireTarget = false;
	requireTargetsInArea = false;

}

std::vector<sf::Vector3i> Ab_CommandingShout::GetTargetArea(sf::Vector3i selectedTile) {
	std::vector<sf::Vector3i> tiles = {};
	return tiles;
}

std::string Ab_CommandingShout::GetDescription() {
	std::string desc = "All allies deal 5% more damage and take 5% less damage for 12s.";
	desc = WordWrap::WrapString(desc, charPerLine);

	return desc;
}

void Ab_CommandingShout::execute(std::vector<ActorPtr>& targets, sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea) {
	if (battleScene != nullptr) {
		auto players = battleScene->GetPlayers(true);

		for (auto p : players) {
			Combat::AddAuraStack(user, p, AuraID::CommandingShout);
		}
	}
}
	