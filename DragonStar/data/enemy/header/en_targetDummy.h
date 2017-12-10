// ==================================
//
// en_targetDummy.h
//
// Data for Target Dummy enemy.
//
// ==================================

#pragma once

#include "../../enemyInfo.h"

class En_TargetDummy : public EnemyInfo {
public:
	En_TargetDummy();

	std::pair<sf::Vector3i, size_t> ExecuteAI(ActorPtr& user, BattleScene& world);
};
