// ==================================
//
// playerClass.cpp
//
// ==================================

#include "playerClass.h"

#include "id/abilityType.h"
#include "id/equipType.h"

std::string PlayerClass::GetName() {
	return name;
}

PlayerClassID PlayerClass::GetPlayerClassID() {
	return playerClassID;
}

std::vector<AbilityType> PlayerClass::GetAbilityTypes() {
	std::vector<AbilityType> result;

	for (auto t : usable) {
		result.push_back(t.first);
	}

	return result;
}

bool PlayerClass::CanEquip(EquipType equipType) {
	if (std::find(equippable.begin(), equippable.end(), equipType) != equippable.end()) {
		return true;
	}
	return false;
}

bool PlayerClass::CanLearn(std::vector<AbilityType> types, unsigned int tier) {
	for (auto u : usable) {
		if (tier <= u.second && std::find(types.begin(), types.end(), u.first) != types.end()) {
			return true;
		}
	}
	return false;
}