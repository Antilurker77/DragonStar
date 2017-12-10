// ==================================
//
// ab_powerStrike.h
//
// Data for Power Strike ability.
//
// ==================================

#include "../../ability.h"

#pragma once

class Ab_PowerStrike : public Ability {
public:
	Ab_PowerStrike();

	std::vector<sf::Vector3i> GetTargetArea(sf::Vector3i selectedTile);
	std::string GetDescription();
protected:
	void execute(std::vector<ActorPtr>& targets, sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea);
};
