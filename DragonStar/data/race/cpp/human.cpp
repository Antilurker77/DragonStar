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

	baseEXPPerLevel = 300;

	baseHP = 400;
	baseMP = 200;
	baseSP = 100;

	baseSTR = 30;
	baseDEX = 30;
	baseINT = 30;
	baseWIS = 30;

	baseVIT = 100;

	bool canFly = false;
	bool canSwim = false;
}