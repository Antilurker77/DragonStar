// ==================================
//
// ab_obliterate.h
//
// Data for Obliterate ability.
//
// ==================================

#pragma once

#include "../../ability.h"

class Ab_Obliterate : public Ability {
public:
	Ab_Obliterate();

	std::vector<sf::Vector3i> GetTargetArea(sf::Vector3i selectedTile);

	std::string GetDescription();
protected:
	void execute(std::vector<ActorPtr>& targets, sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea);
};
