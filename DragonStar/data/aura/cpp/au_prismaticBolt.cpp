// ==================================
//
// au_prismaticBolt.cpp
//
// ==================================

#include "../header/au_prismaticBolt.h"

#include "../../id/abilityID.h"
#include "../../id/attribute.h"
#include "../../id/auraID.h"
#include "../../id/category.h"
#include "../../id/element.h"
#include "../../id/statModType.h"

Au_PrismaticBolt::Au_PrismaticBolt() {
	name = "Prismatic Bolt";
	id = AuraID::PrismaticBolt;
	icon = "prismatic_bolt.png";

	categories = {
		Category::SingleTarget,
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
		StatMod(StatModType::DamageTaken, 0.05, { Category::Any }, { Element::Fire, Element::Ice, Element::Lightning, Element::Poison, Element::Water, Element::Wind, Element::Earth, Element::Light, Element::Dark })
	};

	canCrit = false;

	baseDuration = 800;
	timePerTick = 0;
	maxStacks = 1;
	hasTicks = false;
	fixedDuration = false; // if true, ignore VIT in calculations
	unlimitedDuration = false;
	consumedOnUse = false; // if true, aura will expire when called in combat calculations

	isStun = false;
	isDisarm = false;
	isSilence = false;
	isSlow = false;

	uniquePerActor = true; // determines if one actor can apply multiple copies of aura
	uniqueAura = true; // if true only one copy can be applied regardless of source

	removeAllStacksOnExpiration = false; // Determines whether all stacks or 1 stack are removed when aura expires
}

std::string Au_PrismaticBolt::GetDescription() {
	return "Increases elemental damage taken by 5%.";
}

void Au_PrismaticBolt::OnTick() {

}

void Au_PrismaticBolt::OnExpiry() {

}