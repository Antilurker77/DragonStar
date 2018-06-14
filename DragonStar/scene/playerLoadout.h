// ==================================
//
// playerLoadout.h
//
// Struct containing data from the
// character generation screen. Used
// to build player actor objects.
//
// ==================================

#pragma once

enum class AbilityID;
enum class PlayerClassID;
enum class EquipmentID;
enum class ItemQuality;
enum class RaceID;

#include <array>
#include <string>
#include <vector>

struct PlayerLoadout {
	bool HasData = false;
	
	std::string Name;
	bool IsFemale;
	RaceID Race;
	PlayerClassID PlayerClass;

	// Slot 0: Main-Hand
	// Slot 1: Off-Hand
	// Slot 2: Head
	// Slot 3: Neck
	// Slot 4: Body
	// Slot 5: Hands
	// Slot 6: Ring 1
	// Slot 7: Ring 2
	// Slot 8: Feet
	std::array<EquipmentID, 9> Equipment;

	// Slot 0: Main-Hand
	// Slot 1: Off-Hand
	// Slot 2: Head
	// Slot 3: Neck
	// Slot 4: Body
	// Slot 5: Hands
	// Slot 6: Ring 1
	// Slot 7: Ring 2
	// Slot 8: Feet
	std::array<ItemQuality, 9> EquipmentQuality;

	std::vector<AbilityID> Abilities;

	unsigned int LeftoverGold;
};
