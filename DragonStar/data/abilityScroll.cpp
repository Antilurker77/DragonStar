// ==================================
//
// abilityScroll.cpp
//
// ==================================

#include "abilityScroll.h"

#include "ability.h"
#include "factory.h"
#include "id/abilityType.h"
#include "id/itemQuality.h"

AbilityScroll::AbilityScroll(AbilityID id) {
	AbilityPtr ability = Factory::CreateAbility(id);

	name = "Potion of " + ability->GetName();
	iconFilepath = "potion.png";
	abilityID = id;
	abilityTypes = ability->GetAbilityTypes();
	tier = ability->GetTier();
	weight = 1;

	if (std::find(abilityTypes.begin(), abilityTypes.end(), AbilityType::AstralSpell) != abilityTypes.end() || 
		std::find(abilityTypes.begin(), abilityTypes.end(), AbilityType::AstralHeal) != abilityTypes.end()) {
		itemQuality = ItemQuality::Unique;
	}
	else {
		switch (tier) {
		case 2:
			itemQuality = ItemQuality::Magical;
			break;
		case 3:
			itemQuality = ItemQuality::Rare;
			break;
		case 4:
			itemQuality = ItemQuality::Mythic;
			break;
		default:
			itemQuality = ItemQuality::Common;
			break;
		}
	}
}

AbilityID AbilityScroll::GetAbilityID() {
	return abilityID;
}

std::vector<AbilityType> AbilityScroll::GetAbilityTypes() {
	return abilityTypes;
}

unsigned int AbilityScroll::GetPrice() {
	// todo: price calculation
	return 100u;
}

bool AbilityScroll::IsAbilityScroll() {
	return true;
}