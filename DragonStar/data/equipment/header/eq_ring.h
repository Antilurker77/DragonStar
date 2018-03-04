// ==================================
//
// eq_ring.h
//
// Data for ring equipment.
//
// ==================================

#pragma once

#include "../../equipment.h"

class Eq_SilverRing : public Equipment {
public:
	Eq_SilverRing();
};

class Eq_GoldRing : public Equipment {
public:
	Eq_GoldRing();
};

class Eq_DragoniteRing : public Equipment {
public:
	Eq_DragoniteRing();
};

class Eq_BandOfTwinDisciplines : public Equipment {
public:
	Eq_BandOfTwinDisciplines();
	void OnHit(ActorPtr& user, ActorPtr& targetHit, EventOptions eventOptions, EventResult eventResult, bool isOffHand);
};

class Eq_RingOfVitality : public Equipment {
public:
	Eq_RingOfVitality();
};

class Eq_OmegaRing : public Equipment {
public:
	Eq_OmegaRing();
};