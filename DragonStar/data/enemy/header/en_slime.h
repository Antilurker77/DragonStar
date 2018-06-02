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

	void OnEvent(EventType eventType, ActorPtr& user, ActorPtr& target, BattleScene* battleScene, EventOptions& eventOptions, EventResult& eventResult, bool isOffHand, double& amount);
};
