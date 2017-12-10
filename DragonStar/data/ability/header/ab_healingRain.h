// ==================================
//
// ab_healingRain.h
//
// Data for Healing Rain ability.
//
// ==================================

#pragma once

#include "../../ability.h"

class Ab_HealingRain : public Ability {
public:
	Ab_HealingRain();

	std::vector<sf::Vector3i> GetTargetArea(sf::Vector3i selectedTile);

	std::string GetDescription();
protected:
	void execute(std::vector<ActorPtr>& targets, sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea);
};
