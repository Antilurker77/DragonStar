// ==================================
//
// eq_sword1H.h
//
// Data for all 1H sword equipment.
//
// ==================================

#pragma once

#include "../../equipment.h"

class Eq_IronSword : public Equipment {
public:
	Eq_IronSword();
};

class Eq_Flametongue : public Equipment {
public:
	Eq_Flametongue();
	void OnEvent(EventType eventType, ActorPtr& user, ActorPtr& target, BattleScene* battleScene, EventOptions& eventOptions, EventResult& eventResult, bool isOffHand, double& amount);
};