// ==================================
//
// command.h
//
// Base class for executing actor
// actions.
//
// ==================================

#pragma once

class Actor;

#include <memory>

typedef std::shared_ptr<Actor> ActorPtr;

class Command{
public:
	virtual void Execute(ActorPtr& actor) = 0;
protected:

};

typedef std::shared_ptr<Command> CommandPtr;