// ==================================
//
// human.cpp
//
// ==================================

#include "../header/human.h"

#include "../../id/abilityID.h"
#include "../../id/category.h"
#include "../../id/element.h"
#include "../../id/statModType.h"

Human::Human(){
	name = "Human";

	filepath = "gfx/actor/human";

	activeRacial = AbilityID::RacialCommandingShout;

	passiveRacial = "Avarice";
	passiveDesc = "Increases gold find by 10%.";
	passiveIcon = "gfx/ui/icon/default.png";

	passivePerks = std::vector<StatMod>({
		StatMod(StatModType::GoldFind, 0.1, {Category::Any}) 
	});

	baseEXPPerLevel = 300;

	baseHP = 700;
	baseMP = 200;
	baseSP = 100;

	baseSTR = 50;
	baseDEX = 50;
	baseINT = 50;
	baseWIS = 50;

	baseVIT = 100;

	bool canFly = false;
	bool canSwim = false;
}