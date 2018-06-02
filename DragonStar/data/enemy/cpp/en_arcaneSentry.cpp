// ==================================
//
// en_arcaneSentry.cpp
//
// ==================================

#include "../header/en_arcaneSentry.h"

#include "../../id/abilityID.h"
#include "../../id/auraID.h"
#include "../../id/category.h"
#include "../../id/creatureType.h"
#include "../../id/element.h"
#include "../../id/enemyID.h"
#include "../../id/equipType.h"
#include "../../id/statModType.h"
#include "../../../core/random.h"

En_ArcaneSentry::En_ArcaneSentry() {
	filepath = "common/arcane_sentry.png";

	name = "Arcane Sentry";

	creatureType = CreatureType::Construct;

	baseHP = 1830;
	baseMP = 250;
	baseSP = 50;

	baseSTR = 20;
	baseDEX = 10;
	baseINT = 40;
	baseWIS = 20;

	baseVIT = 100;
	baseArmor = 15;

	canFly = false;
	canSwim = false;

	attackSpeed = 200;
	attackRange = 4;

	attackType = EquipType::UnarmedIntelligence;
	attackElement = { Element::Arcane };
	attackDamage = 25;
	attackMod = 0.5;

	offHandAttackType = EquipType::None;
	offHandAttackElement = { Element::Physical };
	offHandAttackDamage = 0;
	offHandAttackMod = 0;

	baseGold = 20u;
	baseEXP = 35u;
	lootPoints = 150u;

	statMods = {
		StatMod(StatModType::Resistance, 0.3, { Category::Any }, { Element::Arcane }),
		StatMod(StatModType::MPRegen, 3.0)
	};

	abilities = {
		AbilityID::MagicMissile, // 1
		AbilityID::ArcaneBlast // 2
	};
}

Idea En_ArcaneSentry::ExecuteAI(ActorPtr& user, BattleScene& world) {
	Idea idea;
	idea.first = sf::Vector3i(-1, -1, -1);
	idea.second = 0;

	ActorVector players = world.GetPlayers(true);

	if (!players.empty()) {
		players = ActorFilter::WithinRange(players, user, world, 4, false, false);
		if (!players.empty()) {
			auto target = ActorFilter::RandomActor(players);
			idea.first = target->GetHexPosition();
			
			// Arcane Blast, 50% Chance if Available
			if (user->IsAbilityAvailable(2)) {
				int roll = Random::RandInt(0, 1);
				if (roll == 0) {
					idea.second = 2;
					return idea;
				}
			}

			// Magic Missile
			if (user->IsAbilityAvailable(1)) {
				idea.second = 1;
				return idea;
			}

			// Attack
			idea.second = 0;
			return idea;
		}
	}

	return idea;
}