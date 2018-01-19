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

	void OnHit(ActorPtr& targetHit, EventOptions eventOptions, EventResult eventResult);

	std::string GetDescription();
};
