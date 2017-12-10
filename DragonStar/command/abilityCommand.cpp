// ==================================
//
// abilityCommand.cpp
//
// ==================================

#include "abilityCommand.h"
#include "../scene/battleScene.h"
#include "../entity/actor.h"
#include "../ui/messageLog.h"

AbilityCommand::AbilityCommand(size_t abilityIndex, BattleScene& battleScene, sf::Vector3i cursor) {
	this->abilityIndex = abilityIndex;
	this->battleScene = &battleScene;
	this->cursor = cursor;
}

void AbilityCommand::Execute(ActorPtr& user) {
	//std::vector<sf::Vector3i> range = user->GetAbilityRange(abilityIndex);

	// Check if the cursor is in the targeting range.
	//if (std::find(range.begin(), range.end(), cursor) != range.end()) {
		user->UseAbility(abilityIndex, *battleScene, cursor);
	//}
}
