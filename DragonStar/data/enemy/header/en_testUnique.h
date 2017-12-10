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

	std::pair<sf::Vector3i, size_t> ExecuteAI(ActorPtr& user, BattleScene& world);
};