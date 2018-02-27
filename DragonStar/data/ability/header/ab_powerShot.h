// ==================================
//
// ab_powerShot.h
//
// Data for Power Shot ability.
//
// ==================================

#include "../../ability.h"

#pragma once

class Ab_PowerShot : public Ability {
public:
	Ab_PowerShot();

	std::vector<sf::Vector3i> GetTargetArea(sf::Vector3i selectedTile);
	std::string GetDescription();
protected:
	void execute(std::vector<ActorPtr>& targets, sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea);
};
