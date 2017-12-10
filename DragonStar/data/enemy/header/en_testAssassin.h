// ==================================
//
// en_testAssassin.h
//
// Data for Test Enemy enemy.
//
// ==================================

#pragma once

#include "../../enemyInfo.h"

class En_TestAssassin : public EnemyInfo {
public:
	En_TestAssassin();

	std::pair<sf::Vector3i, size_t> ExecuteAI(ActorPtr& user, BattleScene& world);
};