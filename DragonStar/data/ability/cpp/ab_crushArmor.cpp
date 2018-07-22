// ==================================
//
// ab_crushArmor.cpp
//
// ==================================

#include "../header/ab_crushArmor.h"

#include "../../id/abilityID.h"
#include "../../id/abilityType.h"
#include "../../id/attribute.h"
#include "../../id/auraID.h"
#include "../../id/category.h"
#include "../../id/element.h"
#include "../../id/equipType.h"

Ab_CrushArmor::Ab_CrushArmor() {
	setAttackDefault();

	name = "Crush Armor";
	abilityID = AbilityID::CrushArmor;
	icon = "crush_armor.png";

	abilityTypes = {
		AbilityType::MaceSkill
	};

	tier = 1;

	categories = {
		Category::Attack,
		Category::Skill,
		Category::Damaging,
		Category::SingleTarget,
		Category::Direct
	};

	usableWeapons = {
		EquipType::Mace1H,
		EquipType::Mace2H
	};

	spCost = 25;
	cooldown = 1600;

	usage = UseType::Instant;

	requireTargetsInArea = true;
}

std::vector<sf::Vector3i> Ab_CrushArmor::GetTargetArea(sf::Vector3i selectedTile) {
	std::vector<sf::Vector3i> tiles = { selectedTile };
	return tiles;
}

std::string Ab_CrushArmor::GetDescription() {
	std::string damage = "140%";

	if (user != nullptr) {
		damage = std::to_string(Combat::WeaponAttackEstimate(user, 1.4, false, abilityOptions));
	}

	std::string desc = "Swing your mace with tremendous force, dealing #damage " + damage + " #default weapon damage and";
	desc += " reducing the target's armor by 20% for 12s.";
	desc = WordWrap::WrapString(desc, charPerLine);

	desc += "\n\nRequires mace.";

	return desc;
}

void Ab_CrushArmor::execute(std::vector<ActorPtr>& targets, sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea) {
	auto result = Combat::WeaponAttack(user, targets[0], 1.4, false, abilityOptions);
	if (result.DidHit) {
		Combat::AddAuraStack(user, targets[0], AuraID::CrushArmor);
	}
	Combat::WeaponAttack(user, targets[0], offHandBasicMultiplier, true, abilityOptions);
}