// ==================================
//
// au_spellpower.h
//
// Data for Spellpower aura.
//
// ==================================

#include "../../aura.h"

#pragma once

class Au_Spellpower : public Aura {
public:
	Au_Spellpower();

	std::string GetDescription();
};
