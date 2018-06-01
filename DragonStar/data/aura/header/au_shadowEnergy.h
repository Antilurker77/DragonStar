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

	void OnAttack(ActorPtr& targetHit, BattleScene* battleScene, EventOptions eventOptions, EventResult eventResult, bool isOffHand);

	std::string GetDescription();
};
