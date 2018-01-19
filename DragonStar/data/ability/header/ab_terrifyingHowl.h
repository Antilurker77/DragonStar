// ==================================
//
// ab_terrifyingHowl.h
//
// Data for Terrifying Howl ability.
//
// ==================================

#include "../../ability.h"

#pragma once

class Ab_TerrifyingHowl : public Ability {
public:
	Ab_TerrifyingHowl();

	std::vector<sf::Vector3i> GetTargetArea(sf::Vector3i selectedTile);

	std::string GetDescription();
protected:
	void execute(std::vector<ActorPtr>& targets, sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea);
};
