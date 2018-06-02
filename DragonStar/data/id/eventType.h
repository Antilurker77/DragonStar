// ==================================
//
// eventType.h
//
// List of all event types for the
// proc system.
//
// ==================================

#pragma once

enum class EventType {
	PreCalc,
	PreCalcHeal,
	PostCalc,
	PostCalcHeal,
	Attack,
	Hit,
	Heal,
	Attacked,
	Healed,
	Death
};