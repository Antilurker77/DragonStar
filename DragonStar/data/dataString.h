// ==================================
//
// dataString.h
//
// Helper functions that return
// strings based on the given IDs.
//
// ==================================

#pragma once

enum class Category;
enum class Element;
enum class PlayerClassID;
enum class RaceID;
enum class StatModType;

#include "statMod.h"

#include <string>
#include <vector>

namespace DataString {

	// Returns a string for a given vector of categories.
	std::string CategoryString(std::vector<Category>& categories);

	// Returns a string for a given vector of elements.
	std::string ElementString(std::vector<Element>& elements, bool capitalize = false);

	// Returns the name of a given ability.
	std::string AbilityString(AbilityID id);

	// Returns a string based on the given stat mod.
	std::string StatModString(StatMod& statMod);

	// Returns a string based on the given stat mod type.
	std::string StatModTypeString(StatModType statModType);

	// Returns a string based on the given race.
	std::string RaceString(RaceID id);

	// Returns a string based on the given player class.
	std::string PlayerClassString(PlayerClassID id);
}