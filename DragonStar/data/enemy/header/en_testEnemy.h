// ==================================
//
// en_testEnemy.h
//
// Data for Test Enemy enemy.
//
// ==================================

#pragma once

#include "../../enemyInfo.h"

class En_TestEnemy : public EnemyInfo {
public:
	En_TestEnemy();

	Idea ExecuteAI(ActorPtr& user, BattleScene& world);
};