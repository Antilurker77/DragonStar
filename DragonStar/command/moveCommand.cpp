// ==================================
//
// moveCommand.cpp
//
// ==================================

#include "moveCommand.h"

#include "../scene/battleScene.h"
#include "../data/map.h"
#include "../data/tile.h"
#include "../entity/actor.h"

MoveCommand::MoveCommand(BattleScene& w, sf::Vector3i d)
{
	battleScene = &w;
	destination = d;
}

MoveCommand::MoveCommand(BattleScene& w, sf::Vector2i d)
{
	battleScene = &w;
	destination = sf::Vector3i(d.x, -d.x - d.y, d.y);
}

void MoveCommand::Execute(ActorPtr& actor){
	std::vector<sf::Vector3i> path = battleScene->Pathfind(actor, destination);

	// Don't do anything if the path is invalid.
	if (path.size() > 0){
		double moveMod = battleScene->GetMoveCost(actor, path[0]);

		actor->Walk(path[0], moveMod);
	}
}