// ==================================
//
// race.cpp
//
// ==================================

#include "race.h"

std::string Race::GetName(){
	return name;
}

std::string Race::GetFilepath(){
	return filepath;
}

// Gets the ability ID for the race's active racial ability.
AbilityID Race::GetActiveID(){
	return activeRacial;
}

std::string Race::GetPassiveName(){
	return passiveRacial;
}

std::string Race::GetPassiveDesc(){
	return passiveDesc;
}

// Returns the filepath for the passive icon.
std::string Race::GetPassiveIcon(){
	return passiveIcon;
}

std::vector<StatMod> Race::GetPassivePerks(){
	return passivePerks;
}

int Race::GetEXPPerLevel(){
	return baseEXPPerLevel;
}

int Race::GetBaseHP(){
	return baseHP;
}

int Race::GetBaseMP(){
	return baseMP;
}

int Race::GetBaseSP(){
	return baseSP;
}

int Race::GetBaseSTR(){
	return baseSTR;
}

int Race::GetBaseDEX(){
	return baseDEX;
}

int Race::GetBaseINT(){
	return baseINT;
}

int Race::GetBaseWIS(){
	return baseWIS;
}

int Race::GetBaseVIT(){
	return baseVIT;
}

bool Race::CanFly(){
	return canFly;
}

bool Race::CanSwim(){
	return canSwim;
}