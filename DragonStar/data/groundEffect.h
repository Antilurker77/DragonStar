// ==================================
//
// groundEffect.h
//
// Base class for ground effects.
// Ground effects are placed on the
// map and can deal damage/heal or
// have other various effects.
//
// ==================================

#pragma once

class Actor;
class BattleScene;

#include <memory>
#include <string>

typedef std::shared_ptr<Actor> ActorPtr;

class GroundEffect {
public:

	// Sets the world reference.
	void SetWorld(BattleScene* w);

	// Ticks down the duration of the ground effect. If applicable,
	// triggers the OnTick event if ready.
	void Tick();

	// Returns true if ground effect has expired.
	bool IsExpired();

	// Event that occurs when nextTick reaches 0.
	virtual void OnTick();

	// Event that occurs when the ground effect expires.
	virtual void OnExpiry();

protected:
	ActorPtr user;
	BattleScene* battleScene;
	
	std::string name;

	int duration;
	int maxDuration;
	int nextTick;
	int tickTime;

	bool unlimitedDuration;
};
