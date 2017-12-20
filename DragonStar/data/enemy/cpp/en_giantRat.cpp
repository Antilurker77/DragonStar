// ==================================
//
// en_giantRat.cpp
//
// ==================================

#include "../header/en_giantRat.h"

#include "../../../core/random.h"

En_GiantRat::En_GiantRat() {
	filepath = "common/giant_rat.png";

	name = "Giant Rat";

	creatureType = CreatureType::BEAST;

	baseHP = 600;
	baseMP = 55;
	baseSP = 100;

	baseSTR = 18;
	baseDEX = 18;
	baseINT = 6;
	baseWIS = 6;

	baseVIT = 100;
	baseArmor = 25;

	canFly = false;
	canSwim = false;

	attackSpeed = 150;
	attackRange = 1;

	attackType = EquipType::UNARMED_STR;
	attackElement = { Element::PHYSICAL };
	attackDamage = 24;
	attackMod = 0.8;

	offHandAttackType = EquipType::NONE;
	offHandAttackElement = { Element::PHYSICAL };
	offHandAttackDamage = 0;
	offHandAttackMod = 0;

	baseGold = 12u;
	baseEXP = 15u;
	lootPoints = 60u;

	statMods = {
		StatMod(StatModType::RESISTANCE, 0.1,{ Category::ANY },{ Element::POISON })
	};

	abilities = {
		AbilityID::EN_BITE // 1
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