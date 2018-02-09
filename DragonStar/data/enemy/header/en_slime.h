// ==================================
//
// en_slime.h
//
// Data for Slime enemy.
//
// ==================================

#pragma once

#include "../../enemyInfo.h"

class En_Slime : public EnemyInfo {
public:
	En_Slime();

	Idea ExecuteAI(ActorPtr& user, BattleScene& world);

	void OnAttack(ActorPtr& user, ActorPtr& targetHit, EventOptions eventOptions, EventResult eventResult, bool isOffHand);
};
