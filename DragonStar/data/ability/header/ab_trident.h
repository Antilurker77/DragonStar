// ==================================
//
// ab_trident.h
//
// Data for Trident ability.
//
// ==================================

#include "../../ability.h"

#pragma once

class Ab_Trident : public Ability {
public:
	Ab_Trident();

	std::vector<sf::Vector3i> GetTargetArea(sf::Vector3i selectedTile);
	std::string GetDescription();
protected:
	void execute(std::vector<ActorPtr>& targets, sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea);
};
