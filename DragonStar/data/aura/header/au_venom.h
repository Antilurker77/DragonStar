// ==================================
//
// au_venom.h
//
// Data for Venom aura.
//
// ==================================

#include "../../aura.h"

#pragma once

class Au_Venom : public Aura {
public:
	Au_Venom();

	std::string GetDescription();

	void OnTick();
	void OnExpiry();
};
