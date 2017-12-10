// ==================================
//
// moveCommand.h
//
// Command object that moves actors.
// Causes exhaustion.
//
// ==================================

#pragma once

class Actor;
class BattleScene;

#include "command.h"

#include <SFML\System.hpp>

class MoveCommand : public Command {
public:
	MoveCommand(BattleScene& w, sf::Vector3i d);
	MoveCommand(BattleScene& w, sf::Vector2i d);
	void Execute(ActorPtr& actor);
private:
	BattleScene* battleScene;
	sf::Vector3i destination;
};