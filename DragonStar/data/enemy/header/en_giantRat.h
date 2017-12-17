// ==================================
//
// en_giantRat.h
//
// Data for Giant Rat enemy.
//
// ==================================

#pragma once

#include "../../enemyInfo.h"

class En_GiantRat : public EnemyInfo {
public:
	En_GiantRat();

	Idea ExecuteAI(ActorPtr& user, BattleScene& world);
};
