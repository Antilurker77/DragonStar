// ==================================
//
// ab_elementalEnergy.cpp
//
// ==================================

#include "../header/ab_elementalEnergy.h"

#include "../../id/abilityID.h"
#include "../../id/abilityType.h"
#include "../../id/attribute.h"
#include "../../id/auraID.h"
#include "../../id/category.h"
#include "../../id/element.h"
#include "../../../hex/hexMath.h"

Ab_ElementalEnergy::Ab_ElementalEnergy() {
	setHelpfulSpellDefault();

	name = "Elemental Energy";
	abilityID = AbilityID::ElementalEnergy;
	icon = "elemental_energy.png";

	abilityTypes = {
		AbilityType::DarkSpell,
		AbilityType::EarthSpell,
		AbilityType::FireSpell,
		AbilityType::IceSpell,
		AbilityType::LightningSpell,
		AbilityType::PoisonSpell,
		AbilityType::WaterSpell,
		AbilityType::WindSpell,
		AbilityType::LightSpell
	};
	tier = 1;

	categories = {
		Category::Spell,
		Category::SingleTarget
	};

	elements = {
		Element::Fire,
		Element::Ice,
		Element::Lightning,
		Element::Poison,
		Element::Water,
		Element::Wind,
		Element::Earth,
		Element::Light,
		Element::Dark
	};

	castTime = 0;
	cooldown = 12000;
	range = 0;
	aiSearchRange = 0;
	mpCost = 24;

	usage = UseType::Instant;

	requireTarget = false;
	requireTargetsInArea = false;

}

std::vector<sf::Vector3i> Ab_ElementalEnergy::GetTargetArea(sf::Vector3i selectedTile) {
	std::vector<sf::Vector3i> tiles = {};
	return tiles;
}

std::string Ab_ElementalEnergy::GetDescription() {
	std::string desc = "Increases elemental damage dealt by 15% for 20s.";
	desc = WordWrap::WrapString(desc, charPerLine);

	return desc;
}

void Ab_ElementalEnergy::execute(std::vector<ActorPtr>& targets, sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea) {
	Combat::AddAuraStack(user, user, AuraID::ElementalEnergy);
}