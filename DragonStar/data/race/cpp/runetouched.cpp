// ==================================
//
// runetouched.h
//
// ==================================

#include "../header/runetouched.h"

Runetouched::Runetouched() {
	name = "Runetouched";

	filepath = "gfx/actor/runetouched";

	activeRacial = AbilityID::RACIAL_MAGIC_EATER;

	passiveRacial = "Spellweaver";
	passiveDesc = "Increases arcane resistance by 10%. Increases spell critical strike chance by 5%.";
	passiveIcon = "gfx/ui/icon/default.png";

	passivePerks = std::vector<StatMod>({
		StatMod(StatModType::RESISTANCE, 0.1, { Category::ANY }, { Element::ARCANE }),
		StatMod(StatModType::CRIT_CHANCE, 0.05, { Category::SPELL })
	});

	baseEXPPerLevel = 1000;

	baseHP = 200;
	baseMP = 120;
	baseSP = 100;

	baseSTR = 24;
	baseDEX = 18;
	baseINT = 24;
	baseWIS = 15;

	baseVIT = 100;

	bool canFly = false;
	bool canSwim = false;
}