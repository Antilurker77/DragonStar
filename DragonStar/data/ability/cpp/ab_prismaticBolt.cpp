// ==================================
//
// ab_prismaticBolt.cpp
//
// ==================================

#include "../header/ab_prismaticBolt.h"

#include "../../id/abilityID.h"
#include "../../id/abilityType.h"
#include "../../id/attribute.h"
#include "../../id/auraID.h"
#include "../../id/category.h"
#include "../../id/element.h"

Ab_PrismaticBolt::Ab_PrismaticBolt() {
	setHarmfulSpellDefault();

	name = "Prismatic Bolt";
	abilityID = AbilityID::PrismaticBolt;
	icon = "prismatic_bolt.png";

	abilityTypes = {
		AbilityType::FireSpell,
		AbilityType::IceSpell,
		AbilityType::LightningSpell,
		AbilityType::PoisonSpell,
		AbilityType::WaterSpell,
		AbilityType::WindSpell,
		AbilityType::EarthSpell,
		AbilityType::LightSpell,
		AbilityType::DarkSpell
	};
	tier = 1;

	categories = {
		Category::Spell,
		Category::Damaging,
		Category::SingleTarget,
		Category::Direct
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

	castTime = 300;
	range = 4;
	aiSearchRange = range;
	mpCost = 15;
	
	usage = UseType::Cast;

	requireTargetsInArea = true;
	ignoreBodyBlock = false;
}

std::vector<sf::Vector3i> Ab_PrismaticBolt::GetTargetArea(sf::Vector3i selectedTile) {
	std::vector<sf::Vector3i> tiles = { selectedTile };
	return tiles;
}

std::string Ab_PrismaticBolt::GetDescription() {
	std::string damage = "54";

	if (user != nullptr) {
		damage = std::to_string(Combat::ScalingAttackEstimate(user, 54.0, Attribute::INT, abilityOptions));
	}

	std::string desc = "Shoot a bolt of elemental energy at the target, dealing #damage " + damage +
		" #default elemental damage and increasing the amount of elemental damage the target takes by 5% for 8s.";
	desc = WordWrap::WrapString(desc, charPerLine);

	return desc;
}

void Ab_PrismaticBolt::execute(std::vector<ActorPtr>& targets, sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea) {
	auto result = Combat::ScalingAttack(user, targets[0], 54.0, Attribute::INT, abilityOptions);
	if (result.DidHit) {
		Combat::AddAuraStack(user, targets[0], AuraID::PrismaticBolt);
	}
}