// ==================================
//
// waitCommand.h
//
// Command object causes actors to
// wait idlely. Causes exhautsion.
//
// ==================================

#pragma once

#include "command.h"

#include "../entity/actor.h"

class WaitCommand : public Command {
public:
	// Creates a command that causes the actor to wait
	// for 100.
	WaitCommand();

	// Creates a command that causes the actor to wait
	// for the specified amount.
	WaitCommand(int amount);

	void Execute(ActorPtr& actor);
private:
	int timeToWait;
};