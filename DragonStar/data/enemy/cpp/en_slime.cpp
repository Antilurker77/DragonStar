// ==================================
//
// en_slime.cpp
//
// ==================================

#include "../header/en_slime.h"

#include "../../id/abilityID.h"
#include "../../id/auraID.h"
#include "../../id/category.h"
#include "../../id/creatureType.h"
#include "../../id/element.h"
#include "../../id/enemyID.h"
#include "../../id/equipType.h"
#include "../../id/statModType.h"

En_Slime::En_Slime() {
	filepath = "common/slime.png";

	name = "Slime";
	title = "";

	creatureType = CreatureType::Elemental;

	baseHP = 1400;
	baseMP = 25;
	baseSP = 100;

	baseSTR = 1;
	baseDEX = 1;
	baseINT = 1;
	baseWIS = 1;

	baseVIT = 50;
	baseArmor = 0;

	baseMoveSpeed = 50;
	canFly = false;
	canSwim = false;

	attackSpeed = 180;
	attackRange = 1;

	attackType = EquipType::UnarmedStrength;
	attackElement = { Element::Poison, Element::Water };
	attackDamage = 80;
	attackMod = 0.0;

	offHandAttackType = EquipType::None;
	offHandAttackElement = { Element::Physical };
	offHandAttackDamage = 0;
	offHandAttackMod = 0;

	baseGold = 15u;
	baseEXP = 18u;
	lootPoints = 80u;

	statMods = {
		StatMod(StatModType::Resistance, 0.75,{ Category::Any },{ Element::Physical }),
		StatMod(StatModType::Resistance, 0.30,{ Category::Any },{ Element::Poison }),
		StatMod(StatModType::Resistance, 0.30,{ Category::Any },{ Element::Water }),
		StatMod(StatModType::Resistance, 1.00,{ Category::Any },{ Element::Mind }),
		StatMod(StatModType::Resistance, -0.3,{ Category::Any },{ Element::Ice }),
		StatMod(StatModType::Resistance, -0.3,{ Category::Any },{ Element::Lightning })
	};

	abilities = {};
}

Idea En_Slime::ExecuteAI(ActorPtr& user, BattleScene& world) {
	Idea idea;
	idea.first = sf::Vector3i(-1, -1, -1);

	ActorVector players = world.GetPlayers(true);
	players = ActorFilter::Reachable(players, user, world, 1, false, false);
	if (!players.empty()) {
		players = ActorFilter::Closest(players, user->GetHexPosition());
		idea.first = ActorFilter::RandomActor(players)->GetHexPosition();
		idea.second = 0;
	}

	return idea;
}

void En_Slime::OnEvent(EventType eventType, ActorPtr& user, ActorPtr& target, BattleScene* battleScene, EventOptions& eventOptions, EventResult& eventResult, bool isOffHand, double& amount) {
	// OnAttack
	if (eventType == EventType::Attack) {
		if (eventResult.DidHit) {
			Combat::AddAuraStack(user, target, AuraID::SlimeTouch);
		}
	}
}