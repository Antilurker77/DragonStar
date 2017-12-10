// ==================================
//
// au_rendingSlash.h
//
// Data for Rending Slash.
//
// ==================================

#include "../../aura.h"

#pragma once

class Au_RendingSlash : public Aura {
public:
	Au_RendingSlash();

	std::string GetDescription();

	void OnTick();
};
