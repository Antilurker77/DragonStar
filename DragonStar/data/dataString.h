// ==================================
//
// dataString.h
//
// Helper functions that return
// strings based on the given IDs.
//
// ==================================

#pragma once

enum class Element;
enum class StatModType;

#include "statMod.h"

#include <string>
#include <vector>

namespace DataString {

	// Returns a string for a given vector of elements.
	std::string ElementString(std::vector<Element>& elements, bool capitalize = false);

	// Returns a string based on the given stat mod.
	std::string StatModString(StatMod& statMod);

	// Returns a string based on the given stat mod type.
	std::string StatModTypeString(StatModType statModType);
}