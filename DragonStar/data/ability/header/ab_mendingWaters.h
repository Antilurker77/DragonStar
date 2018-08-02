// ==================================
//
// ab_mendingWaters.h
//
// Data for Mending Waters ability.
//
// ==================================

#pragma once

#include "../../ability.h"

class Ab_MendingWaters : public Ability {
public:
	Ab_MendingWaters();

	std::vector<sf::Vector3i> GetTargetArea(sf::Vector3i selectedTile);

	std::string GetDescription();
protected:
	void execute(std::vector<ActorPtr>& targets, sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea);
};

