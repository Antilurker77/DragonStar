// ==================================
//
// au_prismaticBolt.cpp
//
// ==================================

#include "../header/au_prismaticBolt.h"

Au_PrismaticBolt::Au_PrismaticBolt() {
	name = "Prismatic Bolt";
	id = AuraID::PRISMATIC_BOLT;
	icon = "prismatic_bolt.png";

	categories = {
		Category::SINGLE_TARGET,
		Category::SPELL
	};

	elements = {
		Element::FIRE,
		Element::ICE,
		Element::LIGHTNING,
		Element::POISON,
		Element::WATER,
		Element::WIND,
		Element::EARTH,
		Element::LIGHT,
		Element::DARK
	};

	statMods = {
		StatMod(StatModType::DAMAGE_TAKEN, 0.05, { Category::ANY }, { Element::FIRE, Element::ICE, Element::LIGHTNING, Element::POISON, Element::WATER, Element::WIND, Element::EARTH, Element::LIGHT, Element::DARK })
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