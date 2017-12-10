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
	messageLog.AddMessage(actor->GetName() + " waited for " + std::to_string(timeToWait / 100) + "." + std::to_string(timeToWait % 100) + "s.");
}