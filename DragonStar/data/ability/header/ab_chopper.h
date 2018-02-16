// ==================================
//
// ab_chopper.h
//
// Data for Chopper ability.
//
// ==================================

#include "../../ability.h"

#pragma once

class Ab_Chopper : public Ability {
public:
	Ab_Chopper();

	std::vector<sf::Vector3i> GetTargetArea(sf::Vector3i selectedTile);
	std::string GetDescription();
protected:
	void execute(std::vector<ActorPtr>& targets, sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea);
};
