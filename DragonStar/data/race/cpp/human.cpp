// ==================================
//
// human.cpp
//
// ==================================

#include "../header/human.h"

Human::Human(){
	name = "Human";

	filepath = "gfx/actor/human";

	activeRacial = AbilityID::RACIAL_COMMANDING_SHOUT;

	passiveRacial = "Avarice";
	passiveDesc = "Increases gold find by 10%.";
	passiveIcon = "gfx/ui/icon/default.png";

	passivePerks = std::vector<StatMod>({
		StatMod(StatModType::GOLD_FIND, 0.1, {Category::ANY}) 
	});

	baseEXPPerLevel = 1000;

	baseHP = 200;
	baseMP = 100;
	baseSP = 100;

	baseSTR = 20;
	baseDEX = 20;
	baseINT = 20;
	baseWIS = 20;

	baseVIT = 100;

	bool canFly = false;
	bool canSwim = false;
}