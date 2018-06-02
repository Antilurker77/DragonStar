// ==================================
//
// au_bandOfTwinDisciplines.cpp
//
// ==================================

#include "../header/au_bandOfTwinDisciplines.h"

#include "../../id/abilityID.h"
#include "../../id/attribute.h"
#include "../../id/auraID.h"
#include "../../id/category.h"
#include "../../id/element.h"
#include "../../id/statModType.h"

Au_BandOfTwinDisciplines::Au_BandOfTwinDisciplines() {
	name = "Twin Disciplines";
	id = AuraID::BandOfTwinDisciplines;
	icon = "psionic_missile.png";

	categories = {
		Category::Spell
	};

	elements = {
		Element::Mind
	};

	statMods = {
		StatMod(StatModType::Damage, 0.1, { Category::Direct, Category::Spell }, { Element::Mind }),
		StatMod(StatModType::AuraSnapshotPower, 0.1, { Category::Spell }, { Element::Mind })
	};

	canCrit = false;

	baseDuration = 1500;
	timePerTick = 100;
	maxStacks = 5;
	hasTicks = false;
	fixedDuration = false; // if true, ignore VIT in calculations
	unlimitedDuration = false;
	consumedOnUse = true; // if true, aura will expire when called in combat calculations
	isBuff = true;
	multiplyStatModsByStack = true;

	isStun = false;
	isDisarm = false;
	isSilence = false;
	isSlow = false;

	uniquePerActor = true; // determines if one actor can apply multiple copies of aura
	uniqueAura = true; // if true only one copy can be applied regardless of source

	removeAllStacksOnExpiration = true; // Determines whether all stacks or 1 stack are removed when aura expires
}

std::string Au_BandOfTwinDisciplines::GetDescription() {
	std::string desc = "Increases the damage of your next mind ability by " + std::to_string(10 * stackCount) + "%.";
	desc = WordWrap::WrapString(desc, 42);
	return desc;
}