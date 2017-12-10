// ==================================
//
// au_healingRain.h
//
// Data for Healing Rain aura.
//
// ==================================

#include "../../aura.h"

#pragma once

class Au_HealingRain : public Aura {
public:
	Au_HealingRain();

	std::string GetDescription();

	void OnTick();
};