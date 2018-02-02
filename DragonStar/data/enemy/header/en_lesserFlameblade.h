// ==================================
//
// en_lesserFlameblade.h
//
// Data for Lesser Flameblade enemy.
//
// ==================================

#pragma once

#include "../../enemyInfo.h"

class En_LesserFlameblade : public EnemyInfo {
public:
	En_LesserFlameblade();

	std::pair<sf::Vector3i, size_t> ExecuteAI(ActorPtr& user, BattleScene& world);
};
