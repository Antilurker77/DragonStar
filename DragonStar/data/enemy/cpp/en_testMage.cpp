// ==================================
//
// en_testMage.cpp
//
// ==================================

#include "../header/en_testMage.h"

En_TestMage::En_TestMage() {
	filepath = "common/test_mage.png";

	name = "Test Mage";
	title = "";

	creatureType = CreatureType::HUMANOID;

	baseHP = 135;
	baseMP = 360;
	baseSP = 80;

	baseSTR = 18;
	baseDEX = 22;
	baseINT = 32;
	baseWIS = 28;

	baseVIT = 100;
	baseArmor = 15;

	canFly = false;
	canSwim = false;

	attackSpeed = 300;
	attackRange = 1;

	attackType = EquipType::STAFF;
	attackElement = { Element::PHYSICAL };
	attackDamage = 15;
	attackMod = 0.75;

	offHandAttackType = EquipType::NONE;
	offHandAttackElement = { Element::PHYSICAL };
	offHandAttackDamage = 0;
	offHandAttackMod = 0;

	baseGold = 20u;
	baseEXP = 40u;
	lootPoints = 80u;

	statMods = { StatMod(StatModType::RESISTANCE, 0.1, { Category::SPELL }) };
	abilities = { AbilityID::DARK_BOLT, AbilityID::PRISMATIC_BOLT, AbilityID::VENOM };
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
			playersInRange = ActorFilter::DoesNotHaveAura(playersInRange, AuraID::PRISMATIC_BOLT);
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
			playersInRange = ActorFilter::DoesNotHaveAura(playersInRange, AuraID::VENOM);
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