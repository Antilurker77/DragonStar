// ==================================
//
// ab_elementalEnergy.cpp
//
// ==================================

#include "../header/ab_elementalEnergy.h"

Ab_ElementalEnergy::Ab_ElementalEnergy() {
	setHelpfulSpellDefault();

	name = "Elemental Energy";
	abilityID = AbilityID::ELEMENTAL_ENERGY;
	icon = "elemental_energy.png";

	abilityTypes = {
		AbilityType::DARK_SPELL,
		AbilityType::EARTH_SPELL,
		AbilityType::FIRE_SPELL,
		AbilityType::ICE_SPELL,
		AbilityType::LIGHTNING_SPELL,
		AbilityType::POISON_SPELL,
		AbilityType::WATER_SPELL,
		AbilityType::WIND_SPELL,
		AbilityType::LIGHT_SPELL
	};
	tier = 1;

	categories = {
		Category::SPELL,
		Category::SINGLE_TARGET
	};

	elements = {
		Element::FIRE,
		Element::ICE,
		Element::LIGHTNING,
		Element::POISON,
		Element::WATER,
		Element::WIND,
		Element::EARTH,
		Element::LIGHT,
		Element::DARK
	};

	castTime = 0;
	cooldown = 12000;
	range = 0;
	aiSearchRange = 0;
	mpCost = 24;

	usage = UseType::INSTANT;

	requireTarget = false;
	requireTargetsInArea = false;

}

std::vector<sf::Vector3i> Ab_ElementalEnergy::GetTargetArea(sf::Vector3i selectedTile) {
	std::vector<sf::Vector3i> tiles = {};
	return tiles;
}

std::string Ab_ElementalEnergy::GetDescription() {
	std::string desc = "Increases elemental damage dealt by 15% for 20s.";
	return desc;
}

void Ab_ElementalEnergy::execute(std::vector<ActorPtr>& targets, sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea) {
	Combat::AddAuraStack(user, user, AuraID::ELEMENTAL_ENERGY);
}