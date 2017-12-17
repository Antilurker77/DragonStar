// ==================================
//
// en_arcaneSentry.h
//
// Data for Arcane Sentry enemy.
//
// ==================================

#pragma once

#include "../../enemyInfo.h"

class En_ArcaneSentry : public EnemyInfo {
public:
	En_ArcaneSentry();

	Idea ExecuteAI(ActorPtr& user, BattleScene& world);
};
