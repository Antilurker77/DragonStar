// ==================================
//
// au_prismaticBolt.h
//
// Data for Prismatic Bolt aura.
//
// ==================================

#include "../../aura.h"

#pragma once

class Au_PrismaticBolt : public Aura {
public:
	Au_PrismaticBolt();

	std::string GetDescription();

	void OnTick();
	void OnExpiry();
};
