// ==================================
//
// ab_dragonBreath.h
//
// Data for Dragon Breath ability.
//
// ==================================

#include "../../ability.h"

#pragma once

class Ab_DragonBreath : public Ability {
public:
	Ab_DragonBreath();

	std::vector<sf::Vector3i> GetTargetArea(sf::Vector3i selectedTile);

	std::string GetDescription();
protected:
	void execute(std::vector<ActorPtr>& targets, sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea);
};
