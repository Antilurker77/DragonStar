// ==================================
//
// ab_mendWounds.h
//
// Data for Mend Wounds ability.
//
// ==================================

#pragma once

#include "../../ability.h"

class Ab_MendWounds : public Ability {
public:
	Ab_MendWounds();

	std::vector<sf::Vector3i> GetTargetArea(sf::Vector3i selectedTile);

	std::string GetDescription();
protected:
	void execute(std::vector<ActorPtr>& targets, sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea);
};
