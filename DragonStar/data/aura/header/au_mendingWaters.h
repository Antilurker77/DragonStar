// ==================================
//
// au_mendingWaters.h
//
// Data for Mending Waters aura.
//
// ==================================

#include "../../aura.h"

#pragma once

class Au_MendingWaters : public Aura {
public:
	Au_MendingWaters();

	std::string GetDescription();

	void OnTick();
};
