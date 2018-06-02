// ==================================
//
// en_testAssassin.cpp
//
// ==================================

#include "../header/en_testUnique.h"

#include "../../id/abilityID.h"
#include "../../id/auraID.h"
#include "../../id/category.h"
#include "../../id/creatureType.h"
#include "../../id/element.h"
#include "../../id/enemyID.h"
#include "../../id/equipType.h"
#include "../../id/statModType.h"

En_TestUnique::En_TestUnique() {
	filepath = "unique/test_unique.png";

	name = "Testifan";
	title = "Slayer of Testers";

	creatureType = CreatureType::Humanoid;
	isUnique = true;

	baseHP = 6500;
	baseMP = 40;
	baseSP = 130;

	baseSTR = 70;
	baseDEX = 35;
	baseINT = 41;
	baseWIS = 45;

	baseVIT = 100;
	baseArmor = 40;

	canFly = false;
	canSwim = false;

	attackSpeed = 350;
	attackRange = 1;

	attackType = EquipType::Sword2H;
	attackElement = { Element::Physical };
	attackDamage = 100;
	attackMod = 2.0;

	offHandAttackType = EquipType::None;
	offHandAttackElement = { };
	offHandAttackDamage = 0;
	offHandAttackMod = 0;

	baseGold = 75u;
	baseEXP = 400u;
	lootPoints = 400u;

	statMods = { };
	abilities = { AbilityID::PowerStrike };
}

Idea En_TestUnique::ExecuteAI(ActorPtr& user, BattleScene& world) {
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