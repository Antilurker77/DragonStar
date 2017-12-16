// ==================================
//
// waitCommand.cpp
//
// ==================================

#include "waitCommand.h"

#include "../ui/messageLog.h"

WaitCommand::WaitCommand(){
	timeToWait = 100;
}

WaitCommand::WaitCommand(int amount){
	timeToWait = amount;
}

void WaitCommand::Execute(ActorPtr& actor){
	actor->Wait(timeToWait);

	// message log
	std::string msg;
	if (actor->IsPlayer()) {
		msg += "#blue ";
	}
	else {
		msg += "#red ";
	}
	msg += actor->GetName();
	msg += " #aaaaaa > #default Waits ";
	msg += std::to_string(timeToWait / 100) + "." + std::to_string(timeToWait % 100) + "s";
	messageLog.AddMessage(msg);
}