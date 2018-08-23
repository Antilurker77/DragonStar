// ==================================
//
// ab_spellpower.cpp
//
// ==================================

#include "../header/ab_spellpower.h"

#include "../../id/abilityID.h"
#include "../../id/abilityType.h"
#include "../../id/attribute.h"
#include "../../id/auraID.h"
#include "../../id/category.h"
#include "../../id/element.h"
#include "../../../hex/hexMath.h"

Ab_Spellpower::Ab_Spellpower() {
	setHelpfulSpellDefault();

	name = "Spellpower";
	abilityID = AbilityID::Spellpower;
	icon = "intelligence.png";

	abilityTypes = {
		AbilityType::ArcaneSpell,
		AbilityType::FireSpell,
		AbilityType::IceSpell,
		AbilityType::LightningSpell,
		AbilityType::PoisonSpell,
		AbilityType::WaterSpell,
		AbilityType::WindSpell,
		AbilityType::EarthSpell,
		AbilityType::MindSpell,
		AbilityType::LightSpell,
		AbilityType::DarkSpell,
		AbilityType::DivineHeal,
		AbilityType::NatureHeal
	};
	tier = 1;

	categories = {
		Category::Spell,
		Category::SingleTarget
	};

	elements = {
		Element::Arcane,
		Element::Fire,
		Element::Ice,
		Element::Lightning,
		Element::Poison,
		Element::Water,
		Element::Wind,
		Element::Earth,
		Element::Mind,
		Element::Light,
		Element::Dark,
		Element::DivineHeal,
		Element::NatureHeal
	};

	castTime = 0;
	cooldown = 6000;
	range = 0;
	aiSearchRange = 0;
	mpCost = 25;

	usage = UseType::Instant;

	requireTarget = false;
	requireTargetsInArea = false;

}

std::vector<sf::Vector3i> Ab_Spellpower::GetTargetArea(sf::Vector3i selectedTile) {
	std::vector<sf::Vector3i> tiles = {};
	return tiles;
}

std::string Ab_Spellpower::GetDescription() {
	std::string desc = "Increases spell damage, healing, and haste by 10% for 12s.";
	desc = WordWrap::WrapString(desc, charPerLine);

	return desc;
}

void Ab_Spellpower::execute(std::vector<ActorPtr>& targets, sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea) {
	Combat::AddAuraStack(user, user, AuraID::Spellpower);
}