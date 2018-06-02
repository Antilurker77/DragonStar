// ==================================
//
// en_giantRat.cpp
//
// ==================================

#include "../header/en_giantRat.h"

#include "../../id/abilityID.h"
#include "../../id/auraID.h"
#include "../../id/category.h"
#include "../../id/creatureType.h"
#include "../../id/element.h"
#include "../../id/enemyID.h"
#include "../../id/equipType.h"
#include "../../id/statModType.h"
#include "../../../core/random.h"

En_GiantRat::En_GiantRat() {
	filepath = "common/giant_rat.png";

	name = "Giant Rat";

	creatureType = CreatureType::Beast;

	baseHP = 1000;
	baseMP = 55;
	baseSP = 100;

	baseSTR = 30;
	baseDEX = 30;
	baseINT = 6;
	baseWIS = 6;

	baseVIT = 100;
	baseArmor = 25;

	canFly = false;
	canSwim = false;

	attackSpeed = 150;
	attackRange = 1;

	attackType = EquipType::UnarmedStrength;
	attackElement = { Element::Physical };
	attackDamage = 40;
	attackMod = 0.8;

	offHandAttackType = EquipType::None;
	offHandAttackElement = { Element::Physical };
	offHandAttackDamage = 0;
	offHandAttackMod = 0;

	baseGold = 12u;
	baseEXP = 15u;
	lootPoints = 60u;

	statMods = {
		StatMod(StatModType::Resistance, 0.1,{ Category::Any },{ Element::Poison })
	};

	abilities = {
		AbilityID::Bite // 1
	};
}

Idea En_GiantRat::ExecuteAI(ActorPtr& user, BattleScene& world) {
	Idea idea;
	idea.first = sf::Vector3i(-1, -1, -1);
	idea.second = 0;

	ActorVector players = world.GetPlayers(true);

	if (!players.empty()) {
		players = ActorFilter::Reachable(players, user, world, 1, false, false);
		players = ActorFilter::WithinRange(players, user, world, 4, false, false);
		if (!players.empty()) {
			players = ActorFilter::Closest(players, user->GetHexPosition());
			auto target = ActorFilter::RandomActor(players);
			idea.first = target->GetHexPosition();

			// Bite, 75% If Available
			if (user->IsAbilityAvailable(1)) {
				int roll = Random::RandInt(1, 100);
				if (roll <= 75) {
					idea.second = 1;
					return idea;
				}
			}

			// Attack
			idea.second = 0;
			return idea;
		}
	}

	return idea;
}