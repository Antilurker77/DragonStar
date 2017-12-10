// ==================================
//
// vulpine.cpp
//
// ==================================

#include "../header/vulpine.h"

Vulpine::Vulpine(){
	name = "Vulpine";

	filepath = "gfx/actor/vulpine";

	activeRacial = AbilityID::RACIAL_SPIRIT_TAP;

	passiveRacial = "Wild Hunter";
	passiveDesc = "Increases water, wind, and earth resistance by 10%. Increases damage dealt to beasts by 10%.";
	passiveIcon = "gfx/ui/icon/default.png";

	// beast damage nyi
	passivePerks = std::vector<StatMod>({
		StatMod(StatModType::RESISTANCE, 0.1, { Category::ANY }, { Element::WATER, Element::WIND, Element::EARTH } )
	});

	baseEXPPerLevel = 1000;

	baseHP = 160;
	baseMP = 115;
	baseSP = 100;

	baseSTR = 16;
	baseDEX = 23;
	baseINT = 22;
	baseWIS = 25;

	baseVIT = 100;

	bool canFly = false;
	bool canSwim = false;
}