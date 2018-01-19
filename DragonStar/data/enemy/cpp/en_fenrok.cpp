// ==================================
//
// en_fenrok.cpp
//
// ==================================

#include "../header/en_fenrok.h"

#include "../../id/abilityID.h"
#include "../../id/attribute.h"
#include "../../id/auraID.h"
#include "../../id/category.h"
#include "../../id/creatureType.h"
#include "../../id/element.h"
#include "../../id/enemyID.h"
#include "../../id/equipType.h"
#include "../../id/statModType.h"

#include "../../../core/random.h"

En_Fenrok::En_Fenrok() {
	filepath = "unique/fenrok.png";

	name = "Fenrok";
	title = "the Unhunted";

	creatureType = CreatureType::BEAST;
	isUnique = true;

	baseHP = 20000;
	baseMP = 60;
	baseSP = 120;

	baseSTR = 60;
	baseDEX = 40;
	baseINT = 25;
	baseWIS = 20;

	baseVIT = 100;
	baseArmor = 38;

	canFly = false;
	canSwim = false;

	attackSpeed = 180;
	attackRange = 1;

	attackType = EquipType::UNARMED_STR;
	attackElement = { Element::PHYSICAL };
	attackDamage = 40;
	attackMod = 0.8;

	offHandAttackType = EquipType::NONE;
	offHandAttackElement = {};
	offHandAttackDamage = 0;
	offHandAttackMod = 0;

	baseGold = 80u;
	baseEXP = 100u;
	lootPoints = 475u;

	statMods = {
		StatMod(StatModType::CRIT_CHANCE, 0.05)
	};
	abilities = { 
		AbilityID::BITE, // 1
		AbilityID::TERRIFYING_HOWL, // 2
		AbilityID::SHADOW_ENERGY // 3
	};
}

Idea En_Fenrok::ExecuteAI(ActorPtr& user, BattleScene& world) {
	Idea idea;
	idea.first = sf::Vector3i(-1, -1, -1);

	// Shadow Energy
	if (user->IsAbilityAvailable(3) && user->GetAttributePercent(Attribute::HP) <= 0.5 && !user->HasAura(AuraID::SHADOW_ENERGY)) {
		idea.first = user->GetHexPosition();
		idea.second = 3;
		return idea;
	}

	ActorVector players = world.GetPlayers(true);
	if (players.size() > 0) {
		
		// Terrifying Howl, wait for melee range and try to hit most possible targets
		if (user->IsAbilityAvailable(2)) {
			players = ActorFilter::WithinRange(players, user, world, 1, false, false);
			if (!players.empty()) {
				auto range = user->GetAbilityRange(2);
				std::vector<sf::Vector3i> bestTiles;
				size_t maxHit = 0;
				for (auto tile : range) {
					auto aoe = user->GetAbilityAreaOfEffect(2, tile);
					size_t hit = world.GetAbilityTargets(aoe, false, false).size();
					if (hit > maxHit) {
						bestTiles.clear();
						bestTiles.push_back(tile);
						maxHit = hit;
					}
					else if (hit == maxHit) {
						bestTiles.push_back(tile);
					}
				}
				if (!bestTiles.empty()) {
					idea.first = bestTiles[Random::RandSizeT(0, bestTiles.size() - 1)];
					idea.second = 2;
					return idea;
				}
			}
		}
		
		// Bite and Attack
		players = world.GetPlayers(true);
		players = ActorFilter::Reachable(players, user, world, 1, false, false);
		if (players.size() > 0) {
			players = ActorFilter::Closest(players, user->GetHexPosition());
			ActorPtr target = ActorFilter::RandomActor(players);
			idea.first = target->GetHexPosition();
			if (user->IsAbilityAvailable(1)) {
				idea.second = 1;
			}
			else {
				idea.second = 0;
			}
		}
	}

	return idea;
}