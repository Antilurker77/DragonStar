// ==================================
//
// ab_frost.h
//
// Data for Frost ability.
//
// ==================================

#pragma once

#include "../../ability.h"

class Ab_Frost : public Ability {
public:
	Ab_Frost();

	std::vector<sf::Vector3i> GetTargetArea(sf::Vector3i selectedTile);

	std::string GetDescription();
protected:
	void execute(std::vector<ActorPtr>& targets, sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea);
};
