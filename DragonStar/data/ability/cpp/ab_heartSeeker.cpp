// ==================================
//
// ab_heartSeeker.cpp
//
// ==================================

#include "../header/ab_heartSeeker.h"

#include "../../id/abilityID.h"
#include "../../id/abilityType.h"
#include "../../id/attribute.h"
#include "../../id/auraID.h"
#include "../../id/category.h"
#include "../../id/element.h"
#include "../../id/equipType.h"

Ab_HeartSeeker::Ab_HeartSeeker() {
	setAttackDefault();

	name = "Heart Seeker";
	abilityID = AbilityID::HeartSeeker;
	icon = "heart_seeker.png";

	abilityTypes = {
		AbilityType::BowSkill
	};
	tier = 1;

	categories = {
		Category::Attack,
		Category::Damaging,
		Category::SingleTarget,
		Category::Direct
	};

	usableWeapons = {
		EquipType::Bow
	};

	spCost = 15;
	cooldown = 800;

	usage = UseType::Instant;

	requireTargetsInArea = true;
}

std::vector<sf::Vector3i> Ab_HeartSeeker::GetTargetArea(sf::Vector3i selectedTile) {
	std::vector<sf::Vector3i> tiles = { selectedTile };
	return tiles;
}

std::string Ab_HeartSeeker::GetDescription() {
	std::string damage = "140%";

	if (user != nullptr) {
		damage = std::to_string(Combat::WeaponAttackEstimate(user, 1.4, false, abilityOptions));
	}

	std::string desc = "Aim for the target's heart, dealing #damage " + damage + " #default weapon damage and inflicting Heart Broken,";
	desc += "reducing VIT by 25 for 15s.";
	desc = WordWrap::WrapString(desc, 42);

	desc += "\n\nRequires bow.";

	return desc;
}

void Ab_HeartSeeker::execute(std::vector<ActorPtr>& targets, sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea) {
	auto result = Combat::WeaponAttack(user, targets[0], 1.4, false, abilityOptions);
	if (result.DidHit) {
		Combat::AddAuraStack(user, targets[0], AuraID::HeartBroken);
	}
}