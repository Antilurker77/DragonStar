// ==================================
//
// en_fenrok.h
//
// Data for Fenrok enemy.
//
// ==================================

#pragma once

#include "../../enemyInfo.h"

class En_Fenrok : public EnemyInfo {
public:
	En_Fenrok();

	std::pair<sf::Vector3i, size_t> ExecuteAI(ActorPtr& user, BattleScene& world);
};
