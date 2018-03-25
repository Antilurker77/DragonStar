// ==================================
//
// ab_boulder.h
//
// Data for Boulder ability.
//
// ==================================

#pragma once

#include "../../ability.h"

class Ab_Boulder : public Ability {
public:
	Ab_Boulder();

	std::vector<sf::Vector3i> GetTargetArea(sf::Vector3i selectedTile);

	std::string GetDescription();
protected:
	void execute(std::vector<ActorPtr>& targets, sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea);
};


