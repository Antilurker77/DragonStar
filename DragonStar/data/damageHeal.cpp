// ==================================
//
// damageHeal.cpp
//
// ==================================

#include "damageHeal.h"

DamageHeal::DamageHeal(double powerValue, Attribute attribute, std::vector<Category> categories, std::vector<Element> elements) :
	PowerValue(powerValue),
	EffectedAttribute(attribute),
	Categories(categories),
	Elements(elements)
{
}
