// ==================================
//
// en_testMage.cpp
//
// ==================================

#include "../header/en_testMage.h"

#include "../../id/abilityID.h"
#include "../../id/auraID.h"
#include "../../id/category.h"
#include "../../id/creatureType.h"
#include "../../id/element.h"
#include "../../id/enemyID.h"
#include "../../id/equipType.h"
#include "../../id/statModType.h"

En_TestMage::En_TestMage() {
	filepath = "common/test_mage.png";

	name = "Test Mage";
	title = "";

	creatureType = CreatureType::Humanoid;

	baseHP = 1155;
	baseMP = 360;
	baseSP = 80;

	baseSTR = 30;
	baseDEX = 41;
	baseINT = 53;
	baseWIS = 48;

	baseVIT = 100;
	baseArmor = 15;

	canFly = false;
	canSwim = false;

	attackSpeed = 300;
	attackRange = 1;

	attackType = EquipType::Staff;
	attackElement = { Element::Physical };
	attackDamage = 25;
	attackMod = 0.75;

	offHandAttackType = EquipType::None;
	offHandAttackElement = { Element::Physical };
	offHandAttackDamage = 0;
	offHandAttackMod = 0;

	baseGold = 20u;
	baseEXP = 40u;
	lootPoints = 80u;

	statMods = { StatMod(StatModType::Resistance, 0.1, { Category::Spell }) };
	abilities = { AbilityID::DarkBolt, AbilityID::PrismaticBolt, AbilityID::Venom };
}

Idea En_TestMage::ExecuteAI(ActorPtr& user, BattleScene& world) {
	Idea idea;
	idea.first = sf::Vector3i(-1, -1, -1);
	idea.second = 0;

	ActorVector players = world.GetPlayers(true);

	if (players.size() > 0) {
		// Prismatic Bolt
		if (user->IsAbilityAvailable(2)) {
			ActorVector playersInRange = ActorFilter::WithinRange(players, user, world, 4, false, false);
			playersInRange = ActorFilter::DoesNotHaveAura(playersInRange, AuraID::PrismaticBolt);
			if (!playersInRange.empty()) {
				ActorPtr target = ActorFilter::RandomActor(playersInRange);
				idea.first = target->GetHexPosition();
				idea.second = 2;
				return idea;
			}
		}

		// Venom
		if (user->IsAbilityAvailable(3)) {
			ActorVector playersInRange = ActorFilter::WithinRange(players, user, world, 4, false, false);
			playersInRange = ActorFilter::DoesNotHaveAura(playersInRange, AuraID::Venom);
			if (!playersInRange.empty()) {
				ActorPtr target = ActorFilter::RandomActor(playersInRange);
				idea.first = target->GetHexPosition();
				idea.second = 3;
				return idea;
			}
		}

		// Dark Bolt
		if (user->IsAbilityAvailable(1)) {
			players = ActorFilter::Reachable(players, user, world, 4, false, false);
			if (!players.empty()) {
				players = ActorFilter::Closest(players, user->GetHexPosition());
				ActorPtr target = ActorFilter::RandomActor(players);
				idea.first = target->GetHexPosition();
				idea.second = 1;
				return idea;
			}
			// if it can't reach actors within distance 4, melee is impossible
			else {
				return idea;
			}
		}

		players = ActorFilter::Reachable(players, user, world, 1, false, false);
		if (!players.empty()) {
			players = ActorFilter::Closest(players, user->GetHexPosition());
			ActorPtr target = ActorFilter::RandomActor(players);
			idea.first = target->GetHexPosition();
			idea.second = 0;
			return idea;
		}
	}

	return idea;
}