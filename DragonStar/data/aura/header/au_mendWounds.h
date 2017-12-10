// ==================================
//
// au_mendWounds.h
//
// Data for Mend Wounds aura.
//
// ==================================

#include "../../aura.h"

#pragma once

class Au_MendWounds : public Aura {
public:
	Au_MendWounds();

	std::string GetDescription();

	void OnTick();
	void OnExpiry();
};
