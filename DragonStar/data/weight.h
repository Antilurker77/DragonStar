// ==================================
//
// weight.h
//
// Returns vectors that contain the
// RNG weights for formations and
// uniques.
//
// ==================================

#pragma once

enum class AbilityID;
enum class EquipmentID;
enum class FormationID;

#include <vector>

#include "../core/random.h"

typedef std::pair<EquipmentID, double> EquipmentWeight;
typedef std::pair<AbilityID, double> AbilityWeight;
typedef std::pair<FormationID, double> FormationWeight;

namespace Weight {
	
	// Returns the RNG weights for common formations.
	std::vector<FormationWeight> GetCommonFaWeights(int tier);

	// Returns the RNG weights for unique formations.
	std::vector<FormationWeight> GetUniqueFaWeights(int tier);

	// Returns the RNG weights for boss formations.
	std::vector<FormationWeight> GetBossFaWeights(int tier);

	// Returns a random Equipment ID based on tier.
	EquipmentID GetRandomEq(std::mt19937_64& mt, int tier);

	// Returns a random unique Equipment ID based on tier.
	EquipmentID GetRandomUniqueEq(std::mt19937_64& mt, int tier, std::vector<EquipmentID>& existingUniques);

	// Returns a random Ability ID based on tier.
	AbilityID GetRandomAb(std::mt19937_64& mt, int tier);

	// Returns a random Formation ID given a weight table.
	FormationID GetRandomFa(std::mt19937_64& mt, std::vector<FormationWeight>& formations);

	// Removes uniques from a formation weight table.
	void RemoveUniqueFa(std::vector<FormationWeight>& formations, FormationID id);

	// Removes uniques from a formation weight table.
	void RemoveUniqueFa(std::vector<FormationWeight>& formations, std::vector<FormationID> id);
}
