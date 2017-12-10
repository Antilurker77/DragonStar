// ==================================
//
// ab_commandingShout.h
//
// Data for Commanding Shout ability.
//
// ==================================

#pragma once

#include "../../ability.h"

class Ab_CommandingShout : public Ability {
public:
	Ab_CommandingShout();

	std::vector<sf::Vector3i> GetTargetArea(sf::Vector3i selectedTile);

	std::string GetDescription();
protected:
	void execute(std::vector<ActorPtr>& targets, sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea);
};
