// ==================================
//
// ab_fireNova.h
//
// Data for Fire Nova ability.
//
// ==================================

#pragma once

#include "../../ability.h"

class Ab_FireNova : public Ability {
public:
	Ab_FireNova();

	std::vector<sf::Vector3i> GetTargetArea(sf::Vector3i selectedTile);

	std::string GetDescription();
protected:
	void execute(std::vector<ActorPtr>& targets, sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea);
};
