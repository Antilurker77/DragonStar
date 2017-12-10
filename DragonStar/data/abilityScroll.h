// ==================================
//
// abilityScroll.h
//
// Item that teaches the player a
// speficic ability.
//
// ==================================

#pragma once

#include <vector>

#include "id.h"
#include "item.h"

class AbilityScroll : public Item {
public:
	// Initializes the scroll with an ability.
	AbilityScroll(AbilityID id);

	// Returns the ability ID of the ability that the scroll can teach.
	AbilityID GetAbilityID();

	// Returns the ability types of the ability.
	std::vector<AbilityType> GetAbilityTypes();

	// Returns the value of the item.
	unsigned int GetPrice();

	// Returns whether or not the item is an ability scroll.
	bool IsAbilityScroll();

private:
	AbilityID abilityID;
	std::vector<AbilityType> abilityTypes;
};
