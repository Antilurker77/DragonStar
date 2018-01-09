// ==================================
//
// abilityScroll.cpp
//
// ==================================

#include "abilityScroll.h"

#include "ability.h"
#include "factory.h"

AbilityScroll::AbilityScroll(AbilityID id) {
	AbilityPtr ability = Factory::CreateAbility(id);

	name = "Potion of " + ability->GetName();
	iconFilepath = "potion.png";
	abilityID = id;
	abilityTypes = ability->GetAbilityTypes();
	tier = ability->GetTier();
	weight = 1;

	if (std::find(abilityTypes.begin(), abilityTypes.end(), AbilityType::ASTRAL_SPELL) != abilityTypes.end() || 
		std::find(abilityTypes.begin(), abilityTypes.end(), AbilityType::ASTRAL_HEAL) != abilityTypes.end()) {
		itemQuality = ItemQuality::UNIQUE;
	}
	else {
		switch (tier) {
		case 2:
			itemQuality = ItemQuality::MAGICAL;
			break;
		case 3:
			itemQuality = ItemQuality::RARE;
			break;
		case 4:
			itemQuality = ItemQuality::MYTHIC;
			break;
		default:
			itemQuality = ItemQuality::COMMON;
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