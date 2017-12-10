// ==================================
//
// dataString.h
//
// Helper functions that return
// strings based on the given IDs.
//
// ==================================

#pragma once

#include "id.h"
#include "statMod.h"

#include <string>
#include <vector>

namespace DataString {

	// Returns a string for a given vector of elements.
	std::string ElementString(std::vector<Element>& elements, bool capitalize = false);

	// Returns a string based on the given stat mod.
	std::string StatModString(StatMod& statMod);

}