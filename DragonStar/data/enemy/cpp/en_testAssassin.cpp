// ==================================
//
// en_testAssassin.cpp
//
// ==================================

#include "../header/en_testAssassin.h"

#include "../../id/abilityID.h"
#include "../../id/auraID.h"
#include "../../id/category.h"
#include "../../id/creatureType.h"
#include "../../id/element.h"
#include "../../id/enemyID.h"
#include "../../id/equipType.h"
#include "../../id/statModType.h"

En_TestAssassin::En_TestAssassin() {
	filepath = "common/test_assassin.png";

	name = "Test Assassin";
	title = "";

	creatureType = CreatureType::HUMANOID;

	baseHP = 1200;
	baseMP = 40;
	baseSP = 100;

	baseSTR = 35;
	baseDEX = 63;
	baseINT = 43;
	baseWIS = 45;

	baseVIT = 80;
	baseArmor = 25;

	baseMoveSpeed = 30;
	canFly = false;
	canSwim = false;

	attackSpeed = 180;
	attackRange = 1;

	attackType = EquipType::DAGGER;
	attackElement = { Element::PHYSICAL };
	attackDamage = 45;
	attackMod = 0.9;

	offHandAttackType = EquipType::DAGGER;
	offHandAttackElement = { Element::PHYSICAL };
	offHandAttackDamage = 27;
	offHandAttackMod = 0.9;

	baseGold = 15u;
	baseEXP = 30u;
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