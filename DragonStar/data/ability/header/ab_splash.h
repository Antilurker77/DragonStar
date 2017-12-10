// ==================================
//
// ab_splash.h
//
// Data for Splash ability.
//
// ==================================

#pragma once

#include "../../ability.h"

class Ab_Splash : public Ability {
public:
	Ab_Splash();

	std::vector<sf::Vector3i> GetTargetArea(sf::Vector3i selectedTile);

	std::string GetDescription();
protected:
	void execute(std::vector<ActorPtr>& targets, sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea);
};
