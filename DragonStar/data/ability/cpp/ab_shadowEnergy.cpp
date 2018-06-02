// ==================================
//
// ab_shadowEnergy.cpp
//
// ==================================

#include "../header/ab_shadowEnergy.h"

#include "../../id/abilityID.h"
#include "../../id/abilityType.h"
#include "../../id/attribute.h"
#include "../../id/auraID.h"
#include "../../id/category.h"
#include "../../id/element.h"
#include "../../../hex/hexMath.h"

Ab_ShadowEnergy::Ab_ShadowEnergy() {
	setHelpfulSpellDefault();

	name = "Shadow Energy";
	abilityID = AbilityID::ShadowEnergy;
	icon = "dark_bolt.png";

	abilityTypes = {
		AbilityType::DarkSpell
	};
	tier = 1;

	categories = {
		Category::Spell,
		Category::SingleTarget
	};

	elements = {
		Element::Dark
	};

	castTime = 100;
	cooldown = 1000;
	range = 0;
	aiSearchRange = 0;
	mpCost = 30;

	usage = UseType::Instant;

	requireTarget = false;
	requireTargetsInArea = false;

}

std::vector<sf::Vector3i> Ab_ShadowEnergy::GetTargetArea(sf::Vector3i selectedTile) {
	std::vector<sf::Vector3i> tiles = {};
	return tiles;
}

std::string Ab_ShadowEnergy::GetDescription() {
	std::string damage = "20";

	if (user != nullptr) {
		damage = std::to_string(Combat::ScalingAttackEstimate(user, 20.0, Attribute::INT, abilityOptions));
	}
	
	std::string desc = "Attacks deal #damage " + damage + " #default dark damage on hit.";
	desc = WordWrap::WrapString(desc, 42);

	return desc;
}

void Ab_ShadowEnergy::execute(std::vector<ActorPtr>& targets, sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea) {
	Combat::AddAuraStack(user, user, AuraID::ShadowEnergy);
}