// ==================================
//
// playerClass.h
//
// Data class that determines if a
// player can equip an item or use
// an ability.
//
// ==================================

#pragma once

#include <string>
#include <vector>

#include "id.h"

class PlayerClass {
public:
	// Returns the name of this class.
	std::string GetName();

	// Returns the player class ID.
	PlayerClassID GetPlayerClassID();

	// Returns the ability types the player can learn.
	std::vector<AbilityType> GetAbilityTypes();

	// Returns true if the player class can equip this item type.
	bool CanEquip(EquipType equipType);

	// Returns true if the player class can learn this ability type.
	bool CanLearn(std::vector<AbilityType> types, unsigned int tier);


protected:
	std::string name = "Unknown Class";
	PlayerClassID playerClassID = PlayerClassID::ADVENTURER;

	std::vector<EquipType> equippable;
	std::vector<std::pair<AbilityType, unsigned int>> usable; // ability type and max tier

};
