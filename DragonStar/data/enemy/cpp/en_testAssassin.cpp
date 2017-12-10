// ==================================
//
// en_testAssassin.cpp
//
// ==================================

#include "../header/en_testAssassin.h"

En_TestAssassin::En_TestAssassin() {
	filepath = "common/test_assassin.png";

	name = "Test Assassin";
	title = "";

	creatureType = CreatureType::HUMANOID;

	baseHP = 110;
	baseMP = 20;
	baseSP = 100;

	baseSTR = 14;
	baseDEX = 25;
	baseINT = 17;
	baseWIS = 18;

	baseVIT = 80;
	baseArmor = 25;

	canFly = false;
	canSwim = false;

	attackSpeed = 180;
	attackRange = 1;

	attackType = EquipType::DAGGER;
	attackElement = { Element::PHYSICAL };
	attackDamage = 18;
	attackMod = 0.9;

	offHandAttackType = EquipType::DAGGER;
	offHandAttackElement = { Element::PHYSICAL };
	offHandAttackDamage = 18;
	offHandAttackMod = 0.9;

	baseGold = 5u;
	baseEXP = 125u;
	lootPoints = 80u;

	statMods = { StatMod(StatModType::CRIT_CHANCE, 0.2), StatMod(StatModType::DODGE_CHANCE, 0.1) };
	abilities = { AbilityID::POWER_STRIKE };
}

Idea En_TestAssassin::ExecuteAI(ActorPtr& user, BattleScene& world) {
	Idea idea;
	idea.first = sf::Vector3i(-1, -1, -1);

	ActorVector players = world.GetPlayers(true);
	if (players.size() > 0) {
		players = ActorFilter::Reachable(players, user, world, 1, false, false);
		if (players.size() > 0) {
			players = ActorFilter::Closest(players, user->GetHexPosition());
			ActorPtr target = ActorFilter::RandomActor(players);
			idea.first = target->GetHexPosition();
		}
	}

	if (user->IsAbilityAvailable(1)) {
		idea.second = 1;
	}
	else {
		idea.second = 0;
	}

	return idea;
}