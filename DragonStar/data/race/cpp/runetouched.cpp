// ==================================
//
// runetouched.h
//
// ==================================

#include "../header/runetouched.h"

#include "../../id/abilityID.h"
#include "../../id/category.h"
#include "../../id/element.h"
#include "../../id/statModType.h"

Runetouched::Runetouched() {
	name = "Runetouched";

	filepath = "gfx/actor/runetouched";

	activeRacial = AbilityID::RacialMagicEater;

	passiveRacial = "Spellweaver";
	passiveDesc = "Increases arcane resistance by 10%. Increases spell critical strike chance by 5%.";
	passiveIcon = "gfx/ui/icon/default.png";

	passivePerks = std::vector<StatMod>({
		StatMod(StatModType::Resistance, 0.1, { Category::Any }, { Element::Arcane }),
		StatMod(StatModType::CritChance, 0.05, { Category::Spell })
	});

	baseEXPPerLevel = 300;

	baseHP = 400;
	baseMP = 240;
	baseSP = 100;

	baseSTR = 36;
	baseDEX = 25;
	baseINT = 36;
	baseWIS = 21;

	baseVIT = 100;

	bool canFly = false;
	bool canSwim = false;
}