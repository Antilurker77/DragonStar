// ==================================
//
// damageHeal.h
//
// Struct that holds values used for
// damage and healing calculation. 
// Includes damage, atrribute, 
// categories, and elements.
//
// PowerValue: amount to damage/heal
// EffectedAttribute: hp/mp/sp
// Categories: effect categories
// Element: effect elements
//
// ==================================

#pragma once

#include "id.h"
#include <vector>
struct DamageHeal {
	const double PowerValue;
	const Attribute EffectedAttribute;
	const std::vector<Category> Categories;
	const std::vector<Element> Elements;

	DamageHeal(double powerValue, Attribute attribute, std::vector<Category> categories, std::vector<Element> elements);
};