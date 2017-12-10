// ==================================
//
// abilityCommand.h
//
// Command object that makes actors
// use an ability. Causes exhaustion.
//
// ==================================

#pragma once

class Actor;
class BattleScene;

#include <SFML\System.hpp>

#include "command.h"

class AbilityCommand : public Command {
public:
	AbilityCommand(size_t abilityIndex, BattleScene& battleScene, sf::Vector3i cursor);
	void Execute(ActorPtr& user);
private:
	size_t abilityIndex;
	BattleScene* battleScene;
	sf::Vector3i cursor;
};
