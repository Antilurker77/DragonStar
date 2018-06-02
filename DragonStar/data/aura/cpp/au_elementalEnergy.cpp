// ==================================
//
// au_elementalEnergy.cpp
//
// ==================================

#include "../header/au_elementalEnergy.h"

#include "../../id/abilityID.h"
#include "../../id/attribute.h"
#include "../../id/auraID.h"
#include "../../id/category.h"
#include "../../id/element.h"
#include "../../id/statModType.h"

Au_ElementalEnergy::Au_ElementalEnergy() {
	name = "Elemental Energy";
	id = AuraID::ElementalEnergy;
	icon = "elemental_energy.png";

	categories = {
		Category::Spell
	};

	elements = {
		Element::Fire,
		Element::Ice,
		Element::Lightning,
		Element::Poison,
		Element::Water,
		Element::Wind,
		Element::Earth,
		Element::Light,
		Element::Dark
	};

	statMods = {
		StatMod(StatModType::Damage, 0.15,{ Category::Any },{ Element::Fire, Element::Ice, Element::Lightning, Element::Poison, Element::Water, Element::Wind, Element::Earth, Element::Light, Element::Dark })
	};

	canCrit = false;

	baseDuration = 2000;
	timePerTick = 0;
	maxStacks = 1;
	hasTicks = false;
	fixedDuration = false; // if true, ignore VIT in calculations
	unlimitedDuration = false;
	consumedOnUse = false; // if true, aura will expire when called in combat calculations
	isBuff = true;

	isStun = false;
	isDisarm = false;
	isSilence = false;
	isSlow = false;

	uniquePerActor = true; // determines if one actor can apply multiple copies of aura
	uniqueAura = false; // if true only one copy can be applied regardless of source

	removeAllStacksOnExpiration = false; // Determines whether all stacks or 1 stack are removed when aura expires
}

std::string Au_ElementalEnergy::GetDescription() {
	return "Increases elemental damage dealt by 15%.";
}