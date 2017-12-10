// ==================================
//
// ab_heal.h
//
// Data for Heal ability.
//
// ==================================

#pragma once

#include "../../ability.h"

class Ab_Heal : public Ability {
public:
	Ab_Heal();

	std::vector<sf::Vector3i> GetTargetArea(sf::Vector3i selectedTile);

	std::string GetDescription();
protected:
	void execute(std::vector<ActorPtr>& targets, sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea);
};
