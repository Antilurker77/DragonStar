// ==================================
//
// vulpine.cpp
//
// ==================================

#include "../header/vulpine.h"

#include "../../id/abilityID.h"
#include "../../id/category.h"
#include "../../id/element.h"
#include "../../id/statModType.h"

Vulpine::Vulpine(){
	name = "Vulpine";

	filepath = "gfx/actor/vulpine";

	activeRacial = AbilityID::RacialSpiritTap;

	passiveRacial = "Wild Hunter";
	passiveDesc = "Increases water, wind, and earth resistance by 10%. Increases damage dealt to beasts by 10%.";
	passiveIcon = "gfx/ui/icon/default.png";

	// beast damage nyi
	passivePerks = std::vector<StatMod>({
		StatMod(StatModType::Resistance, 0.1, { Category::Any }, { Element::Water, Element::Wind, Element::Earth } )
	});

	baseEXPPerLevel = 300;

	baseHP = 340;
	baseMP = 230;
	baseSP = 100;

	baseSTR = 24;
	baseDEX = 34;
	baseINT = 33;
	baseWIS = 37;

	baseVIT = 100;

	bool canFly = false;
	bool canSwim = false;
}