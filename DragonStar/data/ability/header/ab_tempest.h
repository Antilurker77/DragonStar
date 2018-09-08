// ==================================
//
// ab_tempest.h
//
// Data for Tempest ability.
//
// ==================================

#include "../../ability.h"

#pragma once

class Ab_Tempest : public Ability {
public:
	Ab_Tempest();

	std::vector<sf::Vector3i> GetTargetArea(sf::Vector3i selectedTile);

	std::string GetDescription();
protected:
	void execute(std::vector<ActorPtr>& targets, sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea);
};

