// ==================================
//
// en_shadowStalker.h
//
// Data for Shadow Stalker enemy.
//
// ==================================

#pragma once

#include "../../enemyInfo.h"

class En_ShadowStalker : public EnemyInfo {
public:
	En_ShadowStalker();

	Idea ExecuteAI(ActorPtr& user, BattleScene& world);
};

