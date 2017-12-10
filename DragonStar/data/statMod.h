// ==================================
//
// statmod.h
//
// Class that holds data for modifing
// stats. Includes things like auras
// and gear.
//
// ==================================

#pragma once

#include <vector>
#include "id.h"
#include "../core/combat.h"

class StatMod{
public:

	StatMod(StatModType statMod, double value);
	StatMod(StatModType statMod, double value, std::vector<Category> categories);
	StatMod(StatModType statMod, double value, std::vector<Category> categories, std::vector<Element> element);
	StatMod(StatModType statMod, double value, std::vector<Element> onHitElements, std::vector<Category> categories);
	StatMod(StatModType statMod, double value, std::vector<Element> onHitElements, std::vector<Category> categories, std::vector<Element> element);
	StatMod(StatModType statMod, double value, AbilityID ability);
	StatMod(StatModType statMod, double value, AuraID aura);
	StatMod(StatModType statMod, double value, std::vector<Element> onHitElements, AbilityID ability);
	StatMod(StatModType statMod, double value, std::vector<Element> onHitElements, AuraID aura);
	StatMod(StatMod& copy, int multiplier);

	std::vector<Category> GetCategories();
	std::vector<Element> GetElements();
	AbilityID GetAbility();
	AuraID GetAura();
	StatModType GetStatModType();
	double GetValue();
	std::vector<Element> GetOnHitElements();

	bool MatchesCategories(std::vector<Category> testCategories);

private:
	std::vector<Category> categories;
	std::vector<Element> elements;
	AbilityID ability;
	AuraID aura;
	StatModType statModType;
	double value;
	std::vector<Element> onHitElements;
};

namespace StatModCalc {

	// Gets the value from a vector of statMods. Used for internal stat caluclation.
	void GetStatModValue(double& value, std::vector<StatMod>& statMods, StatModType statModType, bool isMultiplicative);

	// Gets the value from a vector of statMods. Used for internal stat calculation.
	void GetStatModValue(double& value, std::vector<StatMod>& statMods, StatModType statModType, EventOptions& eventOptions, bool isMultiplicative);

	// Returns true if the value is a percent.
	bool IsPercent(StatModType statModType);

	// Returns true if the value is mesuared to the tenth decimal.
	bool IsDecimal(StatModType statModType);
}