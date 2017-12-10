// ==================================
//
// ab_gale.h
//
// Data for Gale ability.
//
// ==================================

#pragma once

#include "../../ability.h"

class Ab_Gale : public Ability {
public:
	Ab_Gale();

	std::vector<sf::Vector3i> GetTargetArea(sf::Vector3i selectedTile);

	std::string GetDescription();
protected:
	void execute(std::vector<ActorPtr>& targets, sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea);
};
