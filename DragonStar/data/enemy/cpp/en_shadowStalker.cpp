// ==================================
//
// en_shadowStalker.cpp
//
// ==================================

#include "../header/en_shadowStalker.h"

#include "../../id/abilityID.h"
#include "../../id/auraID.h"
#include "../../id/category.h"
#include "../../id/creatureType.h"
#include "../../id/element.h"
#include "../../id/enemyID.h"
#include "../../id/equipType.h"
#include "../../id/statModType.h"
#include "../../../core/random.h"

En_ShadowStalker::En_ShadowStalker() {
	filepath = "common/shadow_stalker.png";

	name = "Shadow Stalker";

	creatureType = CreatureType::ELEMENTAL;

	baseHP = 1500;
	baseMP = 200;
	baseSP = 100;

	baseSTR = 35;
	baseDEX = 50;
	baseINT = 30;
	baseWIS = 12;

	baseVIT = 100;
	baseArmor = 5;

	canFly = false;
	canSwim = false;

	attackSpeed = 140;
	attackRange = 1;

	attackType = EquipType::DAGGER;
	attackElement = { Element::DARK };
	attackDamage = 35;
	attackMod = 0.7;

	offHandAttackType = EquipType::DAGGER;
	offHandAttackElement = { Element::DARK };
	offHandAttackDamage = 35;
	offHandAttackMod = 0.7;

	baseGold = 18u;
	baseEXP = 40u;
	lootPoints = 140u;

	statMods = {
		StatMod(StatModType::RESISTANCE, 0.5,{ Category::ANY },{ Element::DARK }),
		StatMod(StatModType::RESISTANCE, -0.5,{ Category::ANY },{ Element::LIGHT })
	};

	abilities = {
		AbilityID::SHADOW_STALK // 1
	};
}

Idea En_ShadowStalker::ExecuteAI(ActorPtr& user, BattleScene& world) {
	Idea idea;
	idea.first = sf::Vector3i(-1, -1, -1);
	idea.second = 0;

	ActorVector players = world.GetPlayers(true);

	if (!players.empty()) {
		// Shadow Stalk
		if (user->IsAbilityAvailable(1)) {
			players = ActorFilter::Reachable(players, user, world, 5, false, true);

			ActorVector teleportTargets;
			for (auto p : players) {
				auto adjacent = Hex::HexRing(p->GetHexPosition(), 1);
				for (auto tile : adjacent) {
					if (world.IsTileWalkable(tile, false, false) && world.IsTileOccupied(tile) == false) {
						teleportTargets.push_back(p);
						break;
					}
				}
			}

			if (!teleportTargets.empty()) {
				auto targetsByArmor = ActorFilter::SortByArmor(teleportTargets);
				std::reverse(targetsByArmor.begin(), targetsByArmor.end());
				targetsByArmor.resize(std::min(2u, targetsByArmor.size()));
				idea.first = ActorFilter::RandomActor(targetsByArmor)->GetHexPosition();
				idea.second = 1;
				return idea;
			}
		}

		// Attack
		players = ActorFilter::Reachable(players, user, world, 1, false, false);
		if (!players.empty()) {
			players = ActorFilter::Closest(players, user->GetHexPosition());
			idea.first = ActorFilter::RandomActor(players)->GetHexPosition();
			idea.second = 0;
			return idea;
		}
	}

	return idea;
}