// ==================================
//
// en_testMage.h
//
// Data for Test Mage enemy.
//
// ==================================

#pragma once

#include "../../enemyInfo.h"

class En_TestMage : public EnemyInfo {
public:
	En_TestMage();

	std::pair<sf::Vector3i, size_t> ExecuteAI(ActorPtr& user, BattleScene& world);
};
