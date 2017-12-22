// ==================================
//
// ab_fireball.h
//
// Data for Fireball ability.
//
// ==================================

#pragma once

#include "../../ability.h"

class Ab_Fireball : public Ability {
public:
	Ab_Fireball();

	std::vector<sf::Vector3i> GetTargetArea(sf::Vector3i selectedTile);

	std::string GetDescription();
protected:
	void execute(std::vector<ActorPtr>& targets, sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea);
};
