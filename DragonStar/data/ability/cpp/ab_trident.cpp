// ==================================
//
// ab_trident.cpp
//
// ==================================

#include "../header/ab_trident.h"

#include "../../id/abilityID.h"
#include "../../id/abilityType.h"
#include "../../id/attribute.h"
#include "../../id/auraID.h"
#include "../../id/category.h"
#include "../../id/element.h"
#include "../../../hex/hexMath.h"

Ab_Trident::Ab_Trident() {
	setHelpfulSpellDefault();

	name = "Trident";
	abilityID = AbilityID::Trident;
	icon = "trident.png";

	abilityTypes = {
		AbilityType::SpearSkill
	};
	tier = 3;

	categories = {
		Category::Skill,
		Category::SingleTarget
	};

	elements = {
		Element::Water
	};

	castTime = 0;
	cooldown = 12000;
	range = 0;
	aiSearchRange = 0;
	mpCost = 40;

	usage = UseType::Instant;

	requireTarget = false;
	requireTargetsInArea = false;

}

std::vector<sf::Vector3i> Ab_Trident::GetTargetArea(sf::Vector3i selectedTile) {
	std::vector<sf::Vector3i> tiles = {};
	return tiles;
}

std::string Ab_Trident::GetDescription() {
	std::string damage = "25";

	if (user != nullptr) {
		damage = std::to_string(Combat::ScalingAttackEstimate(user, 25.0, Attribute::DEX, abilityOptions));
	}

	std::string desc = "Envelope your spear in water, increasing water damage dealt by 30% and causing ";
	desc += "your attacks to deal #damage " + damage + " #default water damage on hit. Lasts 20s.";
	desc = WordWrap::WrapString(desc, charPerLine);

	return desc;
}

void Ab_Trident::execute(std::vector<ActorPtr>& targets, sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea) {
	Combat::AddAuraStack(user, user, AuraID::Trident);
}