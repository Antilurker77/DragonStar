// ==================================
//
// race.h
//
// Determines a player's base stats.
//
// ==================================

#pragma once

#include <string>
#include <vector>
#include "id.h"
#include "statMod.h"

class Race {
public:
	std::string GetName();

	std::string GetFilepath();

	AbilityID GetActiveID();

	std::string GetPassiveName();
	std::string GetPassiveDesc();
	std::string GetPassiveIcon();
	std::vector<StatMod> GetPassivePerks();

	int GetEXPPerLevel();

	int GetBaseHP();
	int GetBaseMP();
	int GetBaseSP();

	int GetBaseSTR();
	int GetBaseDEX();
	int GetBaseINT();
	int GetBaseWIS();

	int GetBaseVIT();

	bool CanFly();
	bool CanSwim();

protected:
	std::string name = "Unknown Race";

	std::string filepath = "gfx/actor/human";

	AbilityID activeRacial = AbilityID::RACIAL_COMMANDING_SHOUT;

	std::string passiveRacial = "No Passive";
	std::string passiveDesc = "This race has no passive ability.";
	std::string passiveIcon = "gfx/ui/icon/default.png";
	std::vector<StatMod> passivePerks;

	int baseEXPPerLevel = 1000;

	int baseHP = 10;
	int baseMP = 1;
	int baseSP = 1;

	int baseSTR = 1;
	int baseDEX = 1;
	int baseINT = 1;
	int baseWIS = 1;

	int baseVIT = 100;

	bool canFly = false;
	bool canSwim = false;

};