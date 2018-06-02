// ==================================
//
// au_shadowEnergy.h
//
// Data for Shadow Energy aura.
//
// ==================================

#include "../../aura.h"

#pragma once

class Au_ShadowEnergy : public Aura {
public:
	Au_ShadowEnergy();

	void OnEvent(EventType eventType, ActorPtr& target, BattleScene* battleScene, EventOptions& eventOptions, EventResult& eventResult, bool isOffHand, double& amount);

	std::string GetDescription();
};
