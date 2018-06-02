// ==================================
//
// en_lesserFlameblade.cpp
//
// ==================================

#include "../header/en_lesserFlameblade.h"

#include "../../id/abilityID.h"
#include "../../id/auraID.h"
#include "../../id/category.h"
#include "../../id/creatureType.h"
#include "../../id/element.h"
#include "../../id/enemyID.h"
#include "../../id/equipType.h"
#include "../../id/statModType.h"

En_LesserFlameblade::En_LesserFlameblade() {
	filepath = "common/lesser_flameblade.png";

	name = "Lesser Flameblade";
	title = "";

	creatureType = CreatureType::Elemental;

	baseHP = 1650;
	baseMP = 225;
	baseSP = 110;

	baseSTR = 55;
	baseDEX = 38;
	baseINT = 45;
	baseWIS = 21;

	baseVIT = 110;
	baseArmor = 8;

	baseMoveSpeed = 35;
	canFly = false;
	canSwim = false;

	attackSpeed = 200;
	attackRange = 1;

	attackType = EquipType::Sword1H;
	attackElement = { Element::Physical, Element::Fire };
	attackDamage = 50;
	attackMod = 1.0;

	offHandAttackType = EquipType::None;
	offHandAttackElement = { Element::Physical };
	offHandAttackDamage = 0;
	offHandAttackMod = 0;

	baseGold = 18u;
	baseEXP = 30u;
	lootPoints = 120u;

	statMods = { 
		StatMod(StatModType::Resistance, 0.5, { Category::Any }, { Element::Fire }),
		StatMod(StatModType::Resistance, -0.5, { Category::Any }, { Element::Water })
	};

	abilities = { 
		AbilityID::FlameSlash, // 1
		AbilityID::FireNova // 2
	};
}

Idea En_LesserFlameblade::ExecuteAI(ActorPtr& user, BattleScene& world) {
	Idea idea;
	idea.first = sf::Vector3i(-1, -1, -1);

	ActorVector players = world.GetPlayers(true);
	players = ActorFilter::Reachable(players, user, world, 1, false, false);
	if (!players.empty()) {
		players = ActorFilter::Closest(players, user->GetHexPosition());
		idea.first = ActorFilter::RandomActor(players)->GetHexPosition();
		
		// Fire Nova
		if (user->IsAbilityAvailable(2) && user->HasAura(AuraID::FlameSlash)) {
			idea.second = 2;
			return idea;
		}
		// Flame Slash
		else if (user->IsAbilityAvailable(1)) {
			idea.second = 1;
			return idea;
		}
		// Attack
		else {
			idea.second = 0;
			return idea;
		}
	}

	return idea;
}