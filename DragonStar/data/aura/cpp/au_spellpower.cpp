// ==================================
//
// au_spellpower.cpp
//
// ==================================

#include "../header/au_spellpower.h"

#include "../../id/abilityID.h"
#include "../../id/attribute.h"
#include "../../id/auraID.h"
#include "../../id/category.h"
#include "../../id/element.h"
#include "../../id/statModType.h"

Au_Spellpower::Au_Spellpower() {
	name = "Spellpower";
	id = AuraID::Spellpower;
	icon = "intelligence.png";

	categories = {
		Category::Spell
	};

	elements = {
		Element::Arcane,
		Element::Fire,
		Element::Ice,
		Element::Lightning,
		Element::Poison,
		Element::Water,
		Element::Wind,
		Element::Earth,
		Element::Mind,
		Element::Light,
		Element::Dark,
		Element::DivineHeal,
		Element::NatureHeal
	};

	statMods = {
		StatMod(StatModType::Damage, 0.10, { Category::Spell }),
		StatMod(StatModType::Healing, 0.10, { Category::Spell }),
		StatMod(StatModType::Haste, 0.10, { Category::Spell })
	};

	canCrit = false;

	baseDuration = 1200;
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

std::string Au_Spellpower::GetDescription() {
	return "Increases spell damage by 10%.\nIncreases spell healing by 10%.\nIncreases spell haste by 10%.";
}