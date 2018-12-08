// ==================================
//
// au_trident.h
//
// Data for Trident aura.
//
// ==================================

#include "../../aura.h"

#pragma once

class Au_Trident : public Aura {
public:
	Au_Trident();

	void OnEvent(EventType eventType, ActorPtr& target, BattleScene* battleScene, EventOptions& eventOptions, EventResult& eventResult, bool isOffHand, double& amount);

	std::string GetDescription();
};
