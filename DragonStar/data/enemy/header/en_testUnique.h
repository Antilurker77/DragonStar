// ==================================
//
// en_testUnique.h
//
// Data for Test Unique enemy.
//
// ==================================

#pragma once

#include "../../enemyInfo.h"

class En_TestUnique : public EnemyInfo {
public:
	En_TestUnique();

	Idea ExecuteAI(ActorPtr& user, BattleScene& world);
};